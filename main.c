#include "get_next_line.h"

int	main(void)
{
	int		fd;
	char	*line;
	int		i;

	fd = open("test.txt", O_RDONLY);
	if (fd < 0)
	{
		perror("open");
		return (1);
	}
	i = 1;
	while (i < 3)
	{
		line = get_next_line(fd);
		//printf("\e[36m%d : [\e[0m%s\e[36m]\e[0m\n", i, line);
		free(line);
		i++;
	}
	printf("--- fin du fichier : %d lignes lues ---\n", i - 1);
	close(fd);
	return (0);
}