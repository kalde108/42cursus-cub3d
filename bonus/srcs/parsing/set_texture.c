/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchillon <kchillon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 01:26:19 by ibertran          #+#    #+#             */
/*   Updated: 2024/05/09 19:59:38 by kchillon         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <errno.h>
#include <string.h>

#include "libft.h"
#include "parsing.h"

static int	set_texture_filepath(char *filepath, t_tex *ptr);
// static int	set_texture_color(char *idtok, char *str, __uint32_t *texture);
// static int	get_color_channel(char *tok,
// 				__uint32_t *color,
// 				int channel,
// 				char *idtok);

int	set_texture(char *tok, char *str, t_identifier id, t_cubscene *ptr)
{
	(void)tok;
	if (set_texture_filepath(str, ptr->texture + id))
		return (1);
	return (0);
}

static int	set_texture_filepath(char *filepath, t_tex *ptr)
{
	char	*dup;

	dup = ft_strdup(filepath);
	if (NULL == dup)
	{
		ft_dprintf(STDERR_FILENO, SCENE_ERR2, FATAL, strerror(errno));
		return (1);
	}
	ptr->filepath = dup;
	return (0);
}
