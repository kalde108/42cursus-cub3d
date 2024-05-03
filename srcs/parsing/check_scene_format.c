/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_scene_format.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 23:01:30 by ibertran          #+#    #+#             */
/*   Updated: 2024/05/01 22:56:13 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "libft.h"
#include "parsing.h"

# include "stdio.h"

int	check_scene_format(char **argv)
{
	int	len;

	if (!argv[0])
	{
		ft_dprintf(STDERR_FILENO, SCENE_ERR, NO_SCENE);
		return (1);
	}
	if (argv[1])
	{
		ft_dprintf(STDERR_FILENO, SCENE_ERR, TOO_MAN_ARG);
		return (1);
	}
	len = ft_strlen(argv[0]);
	if (len < 4 || ft_strcmp(argv[0] + len - 4, ".cub"))
	{
		ft_dprintf(STDERR_FILENO, SCENE_ERR2, argv[0], INVAL_FILE);
		return (1);
	}
	return (0);
}
