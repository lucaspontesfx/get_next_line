/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucda-si <lucda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 19:36:06 by lucda-si          #+#    #+#             */
/*   Updated: 2024/12/08 22:04:27 by lucda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*update_file(char *file)
{
	char	*line;
	size_t	i;
	size_t	j;

	i = 0;
	while (file[i] && file[i] != '\n')
		i++;
	if (!file[i])
	{
		free(file);
		return (NULL);
	}
	i++;
	line = ft_calloc(sizeof(char), ft_strlen(file) - i + 1);
	if (!line)
		return (NULL);
	j = 0;
	while (file[i])
	{
		line[j] = file[i];
		j++;
		i++;
	}
	line[j] = '\0';
	return (free(file), line);
}

char	*extract_line(char *file)
{
	char	*line;
	size_t	i;

	if (!file || !*file)
		return (NULL);
	i = 0;
	while (file[i] != '\0' && file[i] != '\n')
		i++;
	line = ft_calloc(sizeof(char), (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (file[i] != '\0' && file[i] != '\n')
	{
		line[i] = file[i];
		i++;
	}
	if (file[i] == '\n')
		line[i] = '\n';
	line[++i] = '\0';
	return (line);
}

char	*init_file(int fd, char *file)
{
	char	*buffer;
	char	*tmp;
	ssize_t	b_read;

	if (!file)
		file = ft_strdup("");
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (free(file), NULL);
	b_read = 1;
	while (b_read > 0 && !ft_strchr(file, '\n'))
	{
		b_read = read(fd, buffer, BUFFER_SIZE);
		if (b_read == -1)
			return (free(buffer), free(file), NULL);
		buffer[b_read] = '\0';
		tmp = ft_strjoin(file, buffer);
		if (!tmp)
			return (free(buffer), free(file), NULL);
		free(file);
		file = tmp;
	}
	free(buffer);
	return (file);
}

char	*get_next_line(int fd)
{
	static char	*file;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	file = init_file(fd, file);
	if (!file)
		return (NULL);
	line = extract_line(file);
	file = update_file(file);
	return (line);
}
/*
int	main(void)
{
	int	fd;
	char	*res;
	
	fd = open("test.txt", O_RDONLY);

	if (fd < 0)
	{
		printf("Error: cannot read file");
		return (-1);
	}
	res = "init";
	while (res)
	{
		res = get_next_line(fd);
		if (!res)
			break ;
		printf("%s", res);
		free(res);
	}
	close(fd);
	return(0);
}
*/