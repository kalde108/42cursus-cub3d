#include <stdio.h>

#include "cub3d.h"

char	*elem_type_str(int type)
{
	if (type == NONE)
		return ("NONE");
	if (type == WALL)
		return ("WALL");
	if (type == FLOOR)
		return ("FLOOR");
	if (type == PORTAL)
		return ("PORTAL");
	return ("UNKNOWN");
}

void	MEMORY_MAP(t_c3_env *env)
{
	size_t	i;
	size_t	j;
	t_elem	*ptr1;
	// void	*ptr2;

	dprintf(2, "\nMEMORY MAP\n\n");
	dprintf(2, "env: %p\n", env);
		dprintf(2, "\tenv->scene: %p\n", &env->scene);
			dprintf(2, "\t\tenv->scene.elems: %p\n", env->scene.elems);
				i = 0;
				ptr1 = env->scene.elems[WALL];
				// while (ptr1 < (void *)env->scene.elems[FLOOR] && ((t_elem *)ptr1)->frames)
				while (i < MAX_TEXTURE)	
				{
					dprintf(2, "\t\t\tenv->scene.elems[WALL][%zu]: %p\n", i, ptr1);
					j = 0;
					while ((int)j < ptr1->n)
					{
						dprintf(2, "\t\t\t\tenv->scene.elems[WALL][%zu].frames[%zu]: %p\n", i, j, ptr1->frames + j);
							dprintf(2, "\t\t\t\t\tenv->scene.elems[WALL][%zu].frames[%zu].filepath: %p | %s\n", i, j, ptr1->frames[j].filepath, ptr1->frames[j].filepath);
							dprintf(2, "\t\t\t\t\tenv->scene.elems[WALL][%zu].frames[%zu].mlx_img: %p\n", i, j, ptr1->frames[j].mlx_img);
							dprintf(2, "\t\t\t\t\tenv->scene.elems[WALL][%zu].frames[%zu].width: %d\n", i, j, ptr1->frames[j].width);
							dprintf(2, "\t\t\t\t\tenv->scene.elems[WALL][%zu].frames[%zu].height: %d\n", i, j, ptr1->frames[j].height);
							dprintf(2, "\t\t\t\t\tenv->scene.elems[WALL][%zu].frames[%zu].addr: %p\n", i, j, ptr1->frames[j].addr);
							dprintf(2, "\t\t\t\t\tenv->scene.elems[WALL][%zu].frames[%zu].bits_per_pixel: %d\n", i, j, ptr1->frames[j].bits_per_pixel);
							dprintf(2, "\t\t\t\t\tenv->scene.elems[WALL][%zu].frames[%zu].line_length: %d\n", i, j, ptr1->frames[j].line_length);
							dprintf(2, "\t\t\t\t\tenv->scene.elems[WALL][%zu].frames[%zu].endian: %d\n", i, j, ptr1->frames[j].endian);
						j++;
					}
					if (ptr1->n)
					{
						dprintf(2, "\t\t\t\tenv->scene.elems[WALL][%zu].current: %p\n", i, ptr1->current);
						dprintf(2, "\t\t\t\tenv->scene.elems[WALL][%zu].n: %d\n", i, ptr1->n);
						dprintf(2, "\t\t\t\tenv->scene.elems[WALL][%zu].current_frame: %d\n", i, ptr1->current_frame);
						dprintf(2, "\t\t\t\tenv->scene.elems[WALL][%zu].dir: %d\n", i, ptr1->dir);
							dprintf(2, "\t\t\t\t\tenv->scene.elems[WALL][%zu].attr.frametime: %zu\n", i, ptr1->attr.frametime);
							dprintf(2, "\t\t\t\t\tenv->scene.elems[WALL][%zu].attr.animation: %s\n", i, elem_type_str(ptr1->attr.animation));
							dprintf(2, "\t\t\t\t\tenv->scene.elems[WALL][%zu].attr.damage: %d\n", i, ptr1->attr.damage);
							dprintf(2, "\t\t\t\t\tenv->scene.elems[WALL][%zu].attr.hinder: %f\n", i, ptr1->attr.hinder);
							dprintf(2, "\t\t\t\t\tenv->scene.elems[WALL][%zu].attr.walkable: %d\n", i, ptr1->attr.walkable);
					}
					ptr1++;
					i++;
				}
				i = 0;
				ptr1 = env->scene.elems[FLOOR];
				while (i < MAX_TEXTURE)
				{
					dprintf(2, "\t\t\tenv->scene.elems[FLOOR][%zu]: %p\n", i, ptr1);
					j = 0;
					while ((int)j < ptr1->n)
					{
						dprintf(2, "\t\t\t\tenv->scene.elems[FLOOR][%zu].frames[%zu]: %p\n", i, j, ptr1->frames + j);
							dprintf(2, "\t\t\t\t\tenv->scene.elems[FLOOR][%zu].frames[%zu].filepath: %p | %s\n", i, j, ptr1->frames[j].filepath, ptr1->frames[j].filepath);
							dprintf(2, "\t\t\t\t\tenv->scene.elems[FLOOR][%zu].frames[%zu].mlx_img: %p\n", i, j, ptr1->frames[j].mlx_img);
							dprintf(2, "\t\t\t\t\tenv->scene.elems[FLOOR][%zu].frames[%zu].width: %d\n", i, j, ptr1->frames[j].width);
							dprintf(2, "\t\t\t\t\tenv->scene.elems[FLOOR][%zu].frames[%zu].height: %d\n", i, j, ptr1->frames[j].height);
							dprintf(2, "\t\t\t\t\tenv->scene.elems[FLOOR][%zu].frames[%zu].addr: %p\n", i, j, ptr1->frames[j].addr);
							dprintf(2, "\t\t\t\t\tenv->scene.elems[FLOOR][%zu].frames[%zu].bits_per_pixel: %d\n", i, j, ptr1->frames[j].bits_per_pixel);
							dprintf(2, "\t\t\t\t\tenv->scene.elems[FLOOR][%zu].frames[%zu].line_length: %d\n", i, j, ptr1->frames[j].line_length);
							dprintf(2, "\t\t\t\t\tenv->scene.elems[FLOOR][%zu].frames[%zu].endian: %d\n", i, j, ptr1->frames[j].endian);
						j++;
					}
					if (ptr1->n)
					{
						dprintf(2, "\t\t\t\tenv->scene.elems[FLOOR][%zu].current: %p\n", i, ptr1->current);
						dprintf(2, "\t\t\t\tenv->scene.elems[FLOOR][%zu].n: %d\n", i, ptr1->n);
						dprintf(2, "\t\t\t\tenv->scene.elems[FLOOR][%zu].current_frame: %d\n", i, ptr1->current_frame);
						dprintf(2, "\t\t\t\tenv->scene.elems[FLOOR][%zu].dir: %d\n", i, ptr1->dir);
							dprintf(2, "\t\t\t\t\tenv->scene.elems[FLOOR][%zu].attr.frametime: %zu\n", i, ptr1->attr.frametime);
							dprintf(2, "\t\t\t\t\tenv->scene.elems[FLOOR][%zu].attr.animation: %s\n", i, elem_type_str(ptr1->attr.animation));
							dprintf(2, "\t\t\t\t\tenv->scene.elems[FLOOR][%zu].attr.damage: %d\n", i, ptr1->attr.damage);
							dprintf(2, "\t\t\t\t\tenv->scene.elems[FLOOR][%zu].attr.hinder: %f\n", i, ptr1->attr.hinder);
							dprintf(2, "\t\t\t\t\tenv->scene.elems[FLOOR][%zu].attr.walkable: %d\n", i, ptr1->attr.walkable);
					}
					ptr1++;
					i++;
				}
				dprintf(2, "\t\t\tenv->scene.elems[PORTAL]: %p\n", env->scene.elems[PORTAL]);
				i = 0;
				ptr1 = env->scene.elems[PORTAL];
				
				dprintf(2, "\t\t\tenv->scene.elems[PORTAL][%zu]: %p\n", i, ptr1);
				j = 0;
				while ((int)j < ptr1->n)
				{
					dprintf(2, "\t\t\t\tenv->scene.elems[PORTAL][%zu].frames[%zu]: %p\n", i, j, ptr1->frames + j);
						dprintf(2, "\t\t\t\t\tenv->scene.elems[PORTAL][%zu].frames[%zu].filepath: %p | %s\n", i, j, ptr1->frames[j].filepath, ptr1->frames[j].filepath);
						dprintf(2, "\t\t\t\t\tenv->scene.elems[PORTAL][%zu].frames[%zu].mlx_img: %p\n", i, j, ptr1->frames[j].mlx_img);
						dprintf(2, "\t\t\t\t\tenv->scene.elems[PORTAL][%zu].frames[%zu].width: %d\n", i, j, ptr1->frames[j].width);
						dprintf(2, "\t\t\t\t\tenv->scene.elems[PORTAL][%zu].frames[%zu].height: %d\n", i, j, ptr1->frames[j].height);
						dprintf(2, "\t\t\t\t\tenv->scene.elems[PORTAL][%zu].frames[%zu].addr: %p\n", i, j, ptr1->frames[j].addr);
						dprintf(2, "\t\t\t\t\tenv->scene.elems[PORTAL][%zu].frames[%zu].bits_per_pixel: %d\n", i, j, ptr1->frames[j].bits_per_pixel);
						dprintf(2, "\t\t\t\t\tenv->scene.elems[PORTAL][%zu].frames[%zu].line_length: %d\n", i, j, ptr1->frames[j].line_length);
						dprintf(2, "\t\t\t\t\tenv->scene.elems[PORTAL][%zu].frames[%zu].endian: %d\n", i, j, ptr1->frames[j].endian);
					j++;
				}
				if (ptr1->n)
				{
					dprintf(2, "\t\t\t\tenv->scene.elems[PORTAL][%zu].current: %p\n", i, ptr1->current);
					dprintf(2, "\t\t\t\tenv->scene.elems[PORTAL][%zu].n: %d\n", i, ptr1->n);
					dprintf(2, "\t\t\t\tenv->scene.elems[PORTAL][%zu].current_frame: %d\n", i, ptr1->current_frame);
					dprintf(2, "\t\t\t\tenv->scene.elems[PORTAL][%zu].dir: %d\n", i, ptr1->dir);
						dprintf(2, "\t\t\t\t\tenv->scene.elems[PORTAL][%zu].attr.frametime: %zu\n", i, ptr1->attr.frametime);
						dprintf(2, "\t\t\t\t\tenv->scene.elems[PORTAL][%zu].attr.animation: %s\n", i, elem_type_str(ptr1->attr.animation));
						dprintf(2, "\t\t\t\t\tenv->scene.elems[PORTAL][%zu].attr.damage: %d\n", i, ptr1->attr.damage);
						dprintf(2, "\t\t\t\t\tenv->scene.elems[PORTAL][%zu].attr.hinder: %f\n", i, ptr1->attr.hinder);
						dprintf(2, "\t\t\t\t\tenv->scene.elems[PORTAL][%zu].attr.walkable: %d\n", i, ptr1->attr.walkable);
				}
			dprintf(2, "\t\tenv->scene.map: %p\n", env->scene.map);
			dprintf(2, "\t\tenv->scene.width: %d\n", env->scene.width);
			dprintf(2, "\t\tenv->scene.height: %d\n", env->scene.height);
			dprintf(2, "\t\tenv->scene.portals: %p\n", &env->scene.portals);
				dprintf(2, "\t\t\tenv->scene.portals.tab: %p\n", env->scene.portals.tab);
				dprintf(2, "\t\t\tenv->scene.portals.total: %d\n", env->scene.portals.total);
				dprintf(2, "\t\t\tenv->scene.portals.opened: %p\n", env->scene.portals.opened);
				dprintf(2, "\t\t\tenv->scene.portals.opened_count: %d\n", env->scene.portals.opened_count);

		dprintf(2, "\tenv->mlx: %p\n", env->mlx);
		dprintf(2, "\tenv->win: %p\n", env->win);
		dprintf(2, "\tenv->img: %p\n", &env->img);
		dprintf(2, "\tenv->key_state: %p\n", &env->key_state);
		dprintf(2, "\tenv->mouse: %p\n", &env->mouse);
		dprintf(2, "\tenv->player: %p\n", &env->player);
		dprintf(2, "\tenv->monster: %p\n", &env->monster);
		dprintf(2, "\tenv->call_mutex: %p\n", &env->call_mutex);
		dprintf(2, "\tenv->z_buffer: %p\n", env->z_buffer);
		dprintf(2, "\tenv->entities: %p\n", env->entities);
		dprintf(2, "\tenv->entity_count: %p\n", &env->entity_count);
		dprintf(2, "\tenv->frame_time: %p\n", &env->frame_time);
		dprintf(2, "\tenv->frame_timer: %p\n", &env->frame_timer);
		dprintf(2, "\tenv->buffer: %p\n", env->buffer);
	dprintf(2, "\nEND MEMORY MAP\n");
}
