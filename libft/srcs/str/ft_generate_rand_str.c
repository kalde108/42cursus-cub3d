/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_generate_rand_str.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 22:09:05 by ibertran          #+#    #+#             */
/*   Updated: 2024/04/19 22:09:08 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

static int	grs_to_charset(const char *charset, char *str, size_t len)
{
	size_t	i;
	size_t	len_charset;

	len_charset = ft_strlen(charset);
	i = -1;
	while (++i < len)
		str[i] = charset[str[i] % len_charset];
	str[i] = '\0';
	return (0);
}

char	*ft_generate_rand_str(size_t len, const char *charset)
{
	char	*str;
	int		fd;

	fd = open("/dev/urandom", O_RDONLY);
	if (fd == -1)
		return (NULL);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
	{
		close(fd);
		return (NULL);
	}
	if (read(fd, str, len) < 0)
	{
		close(fd);
		free(str);
		return (NULL);
	}
	grs_to_charset(charset, str, len);
	close(fd);
	return (str);
}
