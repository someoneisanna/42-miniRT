/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 12:40:24 by ataboada          #+#    #+#             */
/*   Updated: 2024/06/10 14:28:09 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd, int stop)
{
	static char	*storage[MAX_O];
	char		*line;

	if (stop)
	{
		gnl_extra_free(storage);
		return (NULL);
	}
	if (fd < 0 || BUFFER_SIZE < 1 || fd > MAX_O)
		return (NULL);
	storage[fd] = gnl_read_file(fd, storage[fd]);
	if (!storage[fd])
		return (NULL);
	line = gnl_get_current_line(storage[fd]);
	storage[fd] = gnl_update_storage(storage[fd]);
	if (!*storage[fd])
	{
		free(storage[fd]);
		storage[fd] = NULL;
	}
	return (line);
}

char	*gnl_read_file(int fd, char *storage)
{
	char	*buffer;
	int		bytes_read;

	bytes_read = 42;
	buffer = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	while (bytes_read > 0 && !gnl_strchr(storage, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == 0)
			break ;
		if (bytes_read == -1)
		{
			if (storage)
				free(storage);
			break ;
		}
		buffer[bytes_read] = '\0';
		storage = gnl_merge_strs(storage, buffer);
	}
	free(buffer);
	if (gnl_strclen(storage, '\0') > 0 && bytes_read >= 0)
		return (storage);
	return (NULL);
}

char	*gnl_get_current_line(char *storage)
{
	char	*line;
	size_t	l_nwl;

	l_nwl = gnl_strclen(storage, '\n');
	if (storage[l_nwl] == '\n')
		l_nwl++;
	line = gnl_dupstr(storage, l_nwl);
	if (!line)
		return (NULL);
	return (line);
}

char	*gnl_update_storage(char *storage)
{
	char	*upd_storage;
	size_t	l_nwl;
	size_t	l_nul;

	l_nwl = gnl_strclen(storage, '\n');
	l_nul = gnl_strclen(storage, '\0');
	if (storage[l_nwl] == '\n')
		l_nwl++;
	upd_storage = gnl_dupstr(storage + l_nwl, l_nul - l_nwl + 1);
	if (!upd_storage)
		return (NULL);
	free(storage);
	return (upd_storage);
}

void	gnl_extra_free(char **storage)
{
	int	i;

	i = 0;
	while (i < MAX_O)
	{
		if (storage[i])
			free(storage[i]);
		i++;
	}
}
