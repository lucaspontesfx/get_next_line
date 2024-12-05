/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucda-si <lucda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 18:02:54 by lucda-si          #+#    #+#             */
/*   Updated: 2024/12/05 12:25:17 by lucda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*ft_strdup(const char *str)
{
	size_t	i;
	size_t	len;
	char	*res;

	len = ft_strlen(str);
	res = (char *)malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (str[i])
	{
		res[i] = str[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

char	*next_line(char *file)
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

	if (!file || !*file)//if NULL or empty string
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

char	*read_file(int fd, char *file)
{
	char	*buffer;
	char	*tmp;
	ssize_t	b_read;

	if (!file)
		file = ft_strdup("");
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (free(file), NULL);
	b_read = 1;
	while (!ft_strchr(file, '\n') && b_read > 0)
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
	return (free(buffer), file);
}

char	*get_next_line(int fd)
{
	static char	*file;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	file = read_file(fd, file);
	if (!file)
		return (NULL);
	line = extract_line(file);
	file = next_line(file);
	return (line);
}

int	main(void)
{
	int	fd;
	char	*file;

	fd = open("test.txt", O_RDONLY);
	if (!file)
	{
		printf("Error: cannot read the file");
		return (-1);
	}
	if ((file = get_next_line(fd)) == NULL)
	{
		printf("%s\n", file);
		return (-1);
	}	
	else
		printf("%s", file);
	free(file);
	file = NULL;
	while ((file = get_next_line(fd)) != NULL)
	{
		printf("%s", file);
		free (file);
	}
	close(fd);
	printf("\n");
	return (0);
}
