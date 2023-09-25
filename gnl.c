/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehejun <jaehejun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 21:06:47 by jaehejun          #+#    #+#             */
/*   Updated: 2023/09/25 22:41:37 by jaehejun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
# define BUFFER_SIZE 1

//void	leaks()
//{
//	system("leaks a.out");
//}

char	*get_next_line(int fd)
{
	char	*line;
	int		i;
	int		count;
	char	*buffer;

	//atexit(leaks);
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = (char *)malloc(sizeof(char) * (1000));
	i = 0;
	line[i] = '\0';
	while (1)
	{
		buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE));
		count = read(fd, buffer, BUFFER_SIZE);
		if (count == 0)
		{
			free(buffer);
			break ;
		}
		if (buffer[0] == '\n')
		{
			line[i++] = buffer[0];
			free(buffer);
			break ;
		}
		else
			line[i++] = buffer[0];
		free(buffer);
	}
	line[i] = '\0';
	if (line[0] == '\0')
	{
		free(line);
		return (NULL);
	}
	return (line);
}

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("test.txt", O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		printf("%s\n", line);
		free(line);
	}
	//line = get_next_line(fd);
	//printf("%s\n", line);
	//free(line);
	close(fd);
}
