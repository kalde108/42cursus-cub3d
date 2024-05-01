/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 16:30:06 by ibertran          #+#    #+#             */
/*   Updated: 2024/01/08 19:39:20 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static char	**ft_filltab(char **ptr, char const *s, char c, size_t count);
static void	ft_freeall(char **ptr);
static int	ft_countword(char const *s, char c);

char	**ft_split(char const *s, char c)
{
	char	**ptr;
	size_t	count;

	if (!s)
		return (NULL);
	count = ft_countword(s, c);
	ptr = ft_calloc(count + 1, sizeof(char *));
	if (!ptr)
		return (NULL);
	ptr = ft_filltab(ptr, s, c, count);
	if (!ptr)
		return (NULL);
	return (ptr);
}

static char	**ft_filltab(char **ptr, char const *s, char c, size_t count)
{
	size_t	word;
	size_t	start;
	size_t	end;

	word = 0;
	start = 0;
	while (word < count)
	{
		while (s[start] && s[start] == c)
			start++;
		end = start + 1;
		while (s[end] && s[end] != c)
			end++;
		ptr[word] = ft_substr(s, start, end - start);
		if (!ptr[word])
		{
			ft_freeall(ptr);
			return (NULL);
		}
		word++;
		start = end + 1;
	}
	return (ptr);
}

static void	ft_freeall(char **ptr)
{
	size_t	i;

	i = 0;
	while (ptr[i])
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
}

static int	ft_countword(char const *s, char c)
{
	int		word;
	size_t	i;

	i = 0;
	word = 0;
	while (s && s[i])
	{
		if (s[i] != c && (!s[i + 1] || s[i + 1] == c))
			word++;
		i++;
	}
	return (word);
}
