/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_scene_textures.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 22:03:05 by ibertran          #+#    #+#             */
/*   Updated: 2024/05/16 22:31:16 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>

#include "libft.h"
#include "parsing.h"
#include "cubdef.h"

static int			tokenize_line(char *line, t_cubscene *ptr, bool *defined);
static t_identifier	get_identifier(char *str);
static int			is_defined(char *tok, bool *control);
static t_elem		*get_elem_ptr(t_identifier id, t_elem **textures);

int	get_scene_textures(int fd, t_cubscene *ptr)
{
	bool	defined[ID_COUNT];
	int		status;
	char	*gnl;

	ft_memset(defined, 0, sizeof(bool) * ID_COUNT);
	status = 0;
	while (!status && 0 == get_next_line(fd, &gnl) && gnl)
	{
		ft_replace_char(gnl, '\n', '\0');
		if ('\0' == *gnl)
		{
			free(gnl);
			return (0);
		}
		status = tokenize_line(gnl, ptr, defined);
		free(gnl);
	}
	return (status);
}

static int	tokenize_line(char *line, t_cubscene *ptr, bool *defined)
{
	char			*identifier;
	char			*value;
	t_identifier	id;

	identifier = ft_strtok(line, " ");
	if (identifier)
		id = get_identifier(identifier);
	if (!identifier || id == ID_INVAL || is_defined(identifier, defined + id))
		return (1);
	value = ft_strtok(NULL, " ");
	if (value && set_texture(identifier, value, id, ptr))
		return (1);
	else if (NULL == value)
	{
		ft_dprintf(STDERR_FILENO, SCENE_ERR2, line, MISSING_PATH);
		return (1);
	}
	if (get_attributes(identifier, get_elem_ptr(id, ptr->elems)))
		return (1);
	return (0);
}

static t_identifier	get_identifier(char *str)
{
	const char		*indentifier[] = {WA, WB, WC, WD, WE, WF, WG, WH, WI, WJ,
		WK, WL, WM, WN, WO, WP, WQ, WR, WS, WT, WU, WV, WW, WX, WY, WZ, FA, FB,
		FC, FD, FE, FF, FG, FH, FI, FJ, FK, FL, FM, FN, FO, FP, FQ, FR, FS, FT,
		FU, FV, FW, FX, FY, FZ, CA, CB, CC, CD, CE, CF, CG, CH, CI, CJ, CK, CL,
		CM, CN, CO, CP, CQ, CR, CS, CT, CU, CV, CW, CX, CY, CZ, NULL};
	t_identifier	i;

	i = 0;
	while (indentifier[i])
	{
		if (!ft_strcmp(indentifier[i], str))
			return (i);
		i++;
	}
	ft_dprintf(STDERR_FILENO, SCENE_ERR2, str, INVAL_ID);
	return (ID_INVAL);
}

static int	is_defined(char *tok, bool *control)
{
	if (false == *control)
	{
		*control = true;
		return (0);
	}
	ft_dprintf(STDERR_FILENO, SCENE_ERR2, tok, MULTI_ID);
	return (1);
}

static t_elem	*get_elem_ptr(t_identifier id, t_elem **textures)
{
	if (id <= ID_CZ)
		return (textures[id / 26] + (id % 26));
	// else
	// 	;
	return (0);
}