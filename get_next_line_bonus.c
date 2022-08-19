/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkristen <bkristen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 16:32:07 by bkristen          #+#    #+#             */
/*   Updated: 2021/12/27 20:18:51 by bkristen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*check_reminder(char *reminder)
{
	char	*str;
	int		i;

	i = 0;
	if (!reminder[i])
		return (NULL);
	while (reminder[i] && reminder[i] != '\n')
		i++;
	str = (char *)malloc(sizeof(char) * (i + 2));
	if (!str)
		return (NULL);
	i = 0;
	while (reminder[i] && reminder[i] != '\n')
	{
		str[i] = reminder[i];
		i++;
	}
	if (reminder[i] == '\n')
	{
		str[i] = reminder[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_reminder(char *reminder)
{
	int		i;
	int		c;
	char	*str;

	i = 0;
	while (reminder[i] && reminder[i] != '\n')
		i++;
	if (!reminder[i])
	{
		free(reminder);
		return (NULL);
	}
	str = (char *)malloc(sizeof(char) * (ft_strlen(reminder) - i + 1));
	if (!str)
		return (NULL);
	i++;
	c = 0;
	while (reminder[i])
		str[c++] = reminder[i++];
	str[c] = '\0';
	free(reminder);
	return (str);
}

char	*plus(int fd, char *reminder)
{
	char		*buf;
	int			byte_was_read;

	buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
		return (NULL);
	byte_was_read = 1;
	while (!ft_strchr(reminder, '\n') && byte_was_read != 0 )
	{
		byte_was_read = read(fd, buf, BUFFER_SIZE);
		if (byte_was_read == -1)
		{
			free(buf);
			return (NULL);
		}
		buf[byte_was_read] = '\0';
		reminder = ft_strjoin(reminder, buf);
	}
	free(buf);
	return (reminder);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*reminder[OPEN_MAX];

	if (fd < 0 || BUFFER_SIZE < 1 || read(fd, NULL, 0) < 0)
		return (0);
	reminder[fd] = plus(fd, reminder[fd]);
	if (!reminder[fd])
		return (NULL);
	line = check_reminder(reminder[fd]);
	reminder[fd] = ft_reminder(reminder[fd]);
	return (line);
}
