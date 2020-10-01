#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int	ft_test(char *file)
{
	int		fd;
	int		i;
	int		j;
	char    *line = 0;
	char	*lineadress[66];

	j = 1;
	if (!(fd = open(file, O_RDONLY)))
	{
		printf("\nError in open\n");
		return (0);
	}
	while ((i = get_next_line(fd, &line)) > 0)
	{
		printf("|%s\n", line);
		lineadress[j - 1] = line;
		j++;
	}
	printf("|%s\n", line);
	free(line);
	close(fd);
	return (0);
}

int	ft_marge()
{
	int		fd;
	int		fd2;
	int		i;
	int		j;
	char    *line = 0;

	j = 1;
	if (!(fd = open("half_marge_top", O_RDONLY)))
	{
		printf("\nError in open\n");
		return (0);
	}
	if (!(fd2 = open("half_marge_bottom", O_RDONLY)))
	{
		printf("\nError in open\n");
		return (0);
	}
	while ((i = get_next_line(fd, &line)) > 0)
	{
		printf("%s\n", line);
		free(line);
		j++;
	}
	free(line);
	while ((i = get_next_line(fd2, &line)) > 0)
	{
		printf("%s\n", line);
		free(line);
		j++;
	}
	printf("%s\n", line);
	free(line);
	close(fd);
	close(fd2);
	return (0);
}

int		ft_test_huge(char *file)
{
	int		fd;
	int		i;
	char    *line = 0;

	if (!(fd = open(file, O_RDONLY)))
	{
		printf("\nError in open\n");
		return (0);
	}
	while ((i = get_next_line(fd, &line)) > 0)
		printf("(%d)%s\n", i, line);
	printf("(%d)%s\n", i, line);
	free(line);
	close(fd);
	return (0);
}

int		main(void)
{
	printf("\nTEST 1\n");
	ft_test("test.txt");
	printf("\nTEST 2\n");
	ft_test("alphabet");
	printf("\nTEST 3\n");
	ft_test("empty_lines");
	printf("\nTEST 4\n");
	ft_test("empty_file");
	printf("\nTEST 5\n");
	ft_marge();
	printf("\nTEST 6\n");
	ft_test("4_newlines");
	printf("\n\n");

	//ft_test_huge("bible.txt");
	return (0);
}
