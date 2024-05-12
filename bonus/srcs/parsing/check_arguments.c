/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 23:01:30 by ibertran          #+#    #+#             */
/*   Updated: 2024/05/12 16:22:59 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "libft.h"
#include "parsing.h"
#include "cubdef.h"

static int	check_scene_format(char *arg);

int	check_arguments(int ac, char **av)
{
	if (ac == 1)
	{
		ft_dprintf(STDERR_FILENO, SCENE_ERR, NO_SCENE);
		return (1);
	}
	if (ac > 2)
	{
		ft_dprintf(STDERR_FILENO, SCENE_ERR, TOO_MAN_ARG);
		return (1);
	}
	if (check_scene_format(av[1]))
	{
		return (1);
	}
	return (0);
}

static int	check_scene_format(char *arg)
{
	const int	ext_len = ft_strlen(CUB_EXT);
	int			len;

	len = ft_strlen(arg);
	if (len < ext_len || ft_strcmp(arg + len - ext_len, CUB_EXT))
	{
		ft_dprintf(STDERR_FILENO, SCENE_ERR2, arg, INVAL_FILE);
		return (1);
	}
	return (0);
}
