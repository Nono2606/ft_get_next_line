*This project has been created as part of the 42 curriculum by <login>.*

# get_next_line

## Description

`get_next_line` is a C function that returns one line at a time from a file descriptor, each time it is called. The line is returned with its trailing `\n` (except for the last line of a file if it does not end with one). When there is nothing left to read, or when an error occurs, the function returns `NULL`.

The goal of the project is to learn about:

- **static variables**, to keep state between two calls,
- **file descriptors** and the `read` system call,
- **dynamic memory management** (allocation, ownership, leaks),
- reading data in **chunks of arbitrary size** (`BUFFER_SIZE`) while always returning correct, complete lines.

```c
char *get_next_line(int fd);
```

| Return value | Meaning |
|---|---|
| A string | The next line read from `fd` (includes the `\n` if there is one) |
| `NULL` | End of file reached, or an error occurred (invalid `fd`, `read` failure, allocation failure) |

The returned string is allocated with `malloc`: the caller is responsible for freeing it.

## Instructions

### Files

| File | Content |
|---|---|
| `get_next_line.c` | `get_next_line` and its static helpers (read, extract, clean) |
| `get_next_line_utils.c` | Utility functions (`ft_strlen`, `ft_strjoin`, character search) |
| `get_next_line.h` | Prototypes, includes and the default `BUFFER_SIZE` |

### Compilation

The buffer size is set at compile time with the `-D` flag. If it is not provided, the default value defined in the header is used.

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c -o gnl
```

### Usage

```c
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "get_next_line.h"

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("test.txt", O_RDONLY);
	if (fd < 0)
		return (1);
	line = get_next_line(fd);
	while (line)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}
```

### Testing

```bash
# Several buffer sizes, with AddressSanitizer
for size in 1 2 5 42 100 9999 10000000; do
  cc -Wall -Wextra -Werror -fsanitize=address -g -D BUFFER_SIZE=$size \
     get_next_line.c get_next_line_utils.c main.c -o gnl_$size
  ./gnl_$size
done

# Memory leaks
valgrind --leak-check=full --show-leak-kinds=all ./gnl
```

Cases worth testing: empty file, a single `\n`, only `\n`, a last line with and without a trailing `\n`, a very long line, many short lines, `fd = -1`, a closed `fd`, and standard input (`fd = 0`, end with `Ctrl+D`).

## Algorithm

The function keeps the data that has been read but not yet returned in a `static` string, called the *stash*.

1. **Read**: if the stash does not already contain a `\n`, call `read` with a buffer of `BUFFER_SIZE` bytes and append what was read to the stash. Repeat until a `\n` appears in the stash or `read` returns `0` (end of file). Only the newly read part is searched for the `\n`, so already-scanned data is not scanned again.
2. **Extract**: copy everything in the stash up to and including the first `\n` (or up to the end of the stash if there is none) into a new string. This is the line to return.
3. **Clean**: replace the stash with what remains after the extracted line, and free the old one.
4. **End**: when the stash is empty and `read` returns `0`, the stash is freed and set to `NULL`, and the function returns `NULL`.

Every error path (failed `read`, failed `malloc`) frees the memory it owns before returning `NULL`.

### Design choices

- **Reading in a loop** rather than recursively, so that a very long line with a small `BUFFER_SIZE` does not grow the call stack.
- **Searching without allocating**: checking for a `\n` never allocates memory, so there is nothing to leak on that path.
- **Lazy reading**: `read` is only called when the stash cannot yet provide a full line. This matters when reading from a terminal, where `read` would otherwise block even though a line is already available.

## Resources

- `man 2 read`, `man 3 malloc`, `man 3 free`
- *The C Programming Language*, Kernighan & Ritchie (static storage duration, pointers)
- [Valgrind documentation](https://valgrind.org/docs/manual/manual.html)
- [AddressSanitizer](https://github.com/google/sanitizers/wiki/AddressSanitizerFlags)

### Use of AI

AI was used as a code reviewer during development: it pointed out bugs, edge cases, and memory issues in my own code without providing corrections, and it generated a test file and a `main.c` for testing. All the code in this repository was written and fixed by me, and I can explain every line of it.
