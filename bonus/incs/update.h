#ifndef UPDATE_H
# define UPDATE_H

# include "cub3d.h"

bool	update_portal_status(t_portals *portals, int id);
void	rotate_player(t_player *player, double angle);
void	update_portal_frames(t_elem *portal_tex);
void	update_pos(t_c3_env *env);
void 	player_interaction(t_c3_env *env);

#endif