/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_attributes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 19:41:55 by ibertran          #+#    #+#             */
/*   Updated: 2024/06/10 19:41:56 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "cubdef.h"
#include "libft.h"
#include "cubscene.h"

static int	set_attribute(char *identifier, char *str, t_elem *elem);

int	get_attributes(char *identifier, t_elem *elem)
{
	char	*token;

	init_attributes(&elem->attr);
	token = ft_strtok(NULL, " ");
	while (token)
	{
		if (0 != set_attribute(identifier, token, elem))
			return (-1);
		token = ft_strtok(NULL, " ");
	}
	init_timer(&elem->timer, elem->attr.frametime, AUTO_RESET);
	return (0);
}

static int	set_attribute(char *identifier, char *str, t_elem *elem)
{
	const char			*option[] = {ATTR_1, ATTR_2, ATTR_3, NULL};
	const t_set_attr	f[] = {set_animation_attr, set_frametime_attr,
		set_framestart_attr};
	int					i;
	int					len;

	i = 0;
	while (option[i])
	{
		len = ft_strlen(option[i]);
		if (0 == ft_strncmp(option[i], str, len))
		{
			return ((f[i](identifier, str + len, elem)));
		}
		i++;
	}
	ft_dprintf(STDERR_FILENO, SCENE_ERR3, identifier, str, INVAL_ATTR);
	return (-1);
}
