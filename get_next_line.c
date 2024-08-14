/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peferrei <peferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 10:55:08 by peferrei          #+#    #+#             */
/*   Updated: 2024/05/22 11:32:47 by peferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"

static char	*set_stash(char *stash)
{
	char	*new_stash;
	size_t	i;
	size_t	j;

	if (!stash)
		return (NULL);
	new_stash = stash;
	i = 0;
	j = 0;
	while (stash[i] != '\n' && stash[i] != '\0')
		i++;
	while (stash[j] != '\0')
		j++;
	new_stash = ft_substr(stash, i + 1, j - i);
	if (!new_stash)
		return (free(new_stash), NULL);
	free(stash);
	return (new_stash);
}

static char	*fill_line_buffer(int fd, char *stash, char *buffer)
{
	int	read_size;

	read_size = BUFFER_SIZE;
	while (read_size != 0 && (!ft_strchr(buffer, '\n')))
	{
		read_size = read(fd, buffer, BUFFER_SIZE);
		if (read_size < 0)
			return (free(stash), NULL);
		if (read_size == 0)
			break ;
		buffer[read_size] = '\0';
		stash = ft_strjoin(stash, buffer);
		if (!stash)
			return (NULL);
	}
	return (stash);
}

static char	*check_sorb(char *stash)
{
	if (!stash)
	{
		stash = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
		if (!stash)
			return (free(stash), NULL);
		*stash = 0;
		return (stash);
	}
	return (stash);
}

static char	*to_be_or_not_to_be_free(char	*tobe)
{
	free(tobe);
	tobe = NULL;
	return (tobe);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*buffer;
	char		*result;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = check_sorb(stash);
	buffer = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buffer)
		return (free(stash), NULL);
	*buffer = 0;
	stash = fill_line_buffer(fd, stash, buffer);
	buffer = to_be_or_not_to_be_free(buffer);
	if (stash == NULL || stash[0] == '\0')
	{
		stash = to_be_or_not_to_be_free(stash);
		return (NULL);
	}
	result = ft_strdupn(stash);
	if (result == NULL || result[0] == '\0')
		return (free(stash), free(result), NULL);
	stash = set_stash(stash);
	if (*stash == '\0')
		stash = to_be_or_not_to_be_free(stash);
	return (result);
}
