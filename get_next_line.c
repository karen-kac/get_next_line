/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokono <myokono@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 17:40:04 by myokono           #+#    #+#             */
/*   Updated: 2023/10/19 02:29:47 by myokono          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_from_fd(int fd, char *buf, char *storage)
{
	int		bytes_read;

	while ((bytes_read = read(fd, buf, 4096)) > 0)
	{
		buf[bytes_read] = '\0';
		if (storage)
		{
			char *temp = storage;
			storage = ft_strjoin(storage, buf);
			free(temp);
		}
		else
			storage = ft_strdup(buf);
		if (ft_strchr(storage, '\n'))
			break;
	}
	free(buf);
	return (storage);
}

char		*get_next_line(int fd)
{
	static char	*storage;
	char		*buf;
	char		*newline;
	char		*ret;

	if (fd < 0 || !(buf = (char *)malloc(4097)))
		return (NULL);
	storage = read_from_fd(fd, buf, storage);
	if (!storage || !*storage)
	{
		if (storage)
		{
			free(storage);
			storage = NULL;
		}
		return (NULL);
	}
	if ((newline = ft_strchr(storage, '\n')))
	{
		*newline = '\0';
		ret = ft_strdup(storage);
		if (*(newline + 1) != '\0')
		{
			char *temp = storage;
			storage = ft_strdup(newline + 1);
			free(temp);
		}
		else
		{
			free(storage);
			storage = NULL;
		}
	}
	else
	{
		ret = ft_strdup(storage);
		free(storage);
		storage = NULL;
	}
	return (ret);
}



// #include<stdio.h>

// int main ()
// {
// 	printf("nl:%s\n",get_next_line(1));
// 	return (0);
// }