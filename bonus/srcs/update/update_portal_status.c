/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_portal_status.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 19:42:30 by ibertran          #+#    #+#             */
/*   Updated: 2024/06/10 19:42:31 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cubscene.h"

static void	close_portal(t_portals *portals, t_portal *target);
static void	open_portal(t_portals *portals, t_portal *target);

bool	update_portal_status(t_portals *portals, int id)
{
	if (true == portals->tab[id].is_open)
	{
		close_portal(portals, portals->tab + id);
	}
	else if (2 != portals->opened_count)
	{
		open_portal(portals, portals->tab + id);
	}
	else
		return (false);
	return (true);
}

static void	close_portal(t_portals *portals, t_portal *target)
{
	t_portal	*link;

	target->is_open = false;
	portals->opened_count--;
	if (1 == portals->opened_count)
	{
		link = portals->tab + target->linked_portal;
		link->linked_portal = NO_LINK;
		portals->opened[0] = link->id;
	}
	else
	{
		portals->opened[0] = NO_LINK;
	}
	target->linked_portal = NO_LINK;
	portals->opened[1] = NO_LINK;
}

static void	open_portal(t_portals *portals, t_portal *target)
{
	t_portal	*link;

	target->is_open = true;
	portals->opened_count++;
	if (1 == portals->opened_count)
	{
		portals->opened[1] = NO_LINK;
	}
	else
	{
		link = portals->tab + *portals->opened;
		portals->opened[1] = link->id;
		target->linked_portal = link->id;
		link->linked_portal = target->id;
	}
	portals->opened[0] = target->id;
}
