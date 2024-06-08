#ifndef UPDATE_H
# define UPDATE_H

# include "cub3d.h"

void	cub_options(t_c3_env *env);
void 	player_interaction(t_c3_env *env);
void	update_mouse(t_c3_env *env);
void	update_frames(t_c3_env *env);
void	update_player(t_c3_env *env);

bool	update_portal_status(t_portals *portals, int id);
void	rotate_player(t_player *player, double angle);
void	update_portal_frames(t_elem *portal_tex);
void	update_pos(t_c3_env *env);

#endif