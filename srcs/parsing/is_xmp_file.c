/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_xmp_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 01:43:26 by ibertran          #+#    #+#             */
/*   Updated: 2024/05/04 01:45:33 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "libft.h"
#include "parsing.h"

int	is_xmp_file(char *filepath)
{
	const int	len = ft_strlen(filepath);

	if (len < 4 || ft_strcmp(filepath + len - 4, XMP_EXT))
	{
		ft_dprintf(STDERR_FILENO, SCENE_ERR2, filepath, INVAL_PATH);
		return (1);
	}
	return (0);
}
