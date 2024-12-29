/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucda-si <lucda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 10:38:31 by lucda-si          #+#    #+#             */
/*   Updated: 2024/12/08 19:12:51 by lucda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		i++;
	}
	return (i);
}

char	*ft_strchr(const char *str, int c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == (char)c)
			return ((char *)&str[i]);
		i++;
	}
	if ((char)c == '\0')
		return ((char *)&str[i]);
	return (NULL);
}

char	*ft_strdup(const char *str)
{
	size_t	i;
	size_t	len;
	char	*res;

	if (!str)
		return (NULL);
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

char	*ft_strjoin(const char *s1, const char *s2)
{
	int		i;
	int		j;
	size_t	size;
	char	*dest;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	size = ft_strlen(s1) + ft_strlen(s2);
	dest = (char *)malloc(sizeof(char) * (size + 1));
	if (!dest)
		return (NULL);
	i = -1;
	while (s1[++i])
		dest[i] = s1[i];
	j = -1;
	while (s2[++j])
		dest[i++] = s2[j];
	dest[i] = '\0';
	return (dest);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	size_t	i;
	size_t	total;

	if ((nmemb > 2147483647 && size != 0) || (size > 2147483647 && nmemb != 0))
		return (0);
	ptr = malloc(nmemb * size);
	if (!ptr)
		return (NULL);
	i = 0;
	total = nmemb * size;
	while (i < total)
	{
		((unsigned char *)ptr)[i] = 0;
		i++;
	}
	return (ptr);
}
