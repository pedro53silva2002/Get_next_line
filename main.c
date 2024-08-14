/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peferrei <peferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:40:02 by peferrei          #+#    #+#             */
/*   Updated: 2024/05/22 11:03:21 by peferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"

int	main(void)
{
	int		fd;
	char	*str;
	//int i = 2;
	fd = open("text.txt", O_RDONLY);
	str = "";
	/* str = get_next_line(fd);
	printf("%s", str); */
	/*printf("Just one line :\t%s\n", get_next_line(fd));
	printf("Now the rest:\n");*/
	//printf("FD: %d\n", fd);
	while (fd)
	{
		str = get_next_line(fd);
		if (!str)
		{
			//printf("NULL");
			return (0);
		}
		printf("%s", str);
		free(str);
		str = NULL;
	}
	/* while (i--)
	{
		str = get_next_line(0);
		if (!str)
		{
			//printf("NULL");
			return (0);
		}
		printf("%s", str);
		free(str);
		str = NULL;
	} */
	//printf("NULL2");
	close(fd);
	return (0);
}