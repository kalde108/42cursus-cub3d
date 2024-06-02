#ifndef UPDATE_H
# define UPDATE_H


# include "cub3d.h"

void	update_portal_frames(t_elem *portal_tex);
void	update_pos(t_c3_env *env);
void	rotate_player(t_player *player, double angle);

#endif