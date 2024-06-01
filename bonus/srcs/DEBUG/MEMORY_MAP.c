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

char	*portal_face_str(int face)
{
	if (face == 0)
		return ("SOUTH");
	if (face == 1)
		return ("WEST");
	if (face == 2)
		return ("NORTH");
	if (face == 3)
		return ("EAST");
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
		dprintf(2, "\t->scene: %p\n", &env->scene);
			dprintf(2, "\t\t.elems: %p\n", env->scene.elems);
				i = 0;
				ptr1 = env->scene.elems[WALL];
				// while (ptr1 < (void *)env->scene.elems[FLOOR] && ((t_elem *)ptr1)->frames)
				while (i < MAX_TEXTURE)	
				{
					dprintf(2, "\t\t\t[WALL][%zu]: %p\n", i, ptr1);
					j = 0;
					while ((int)j < ptr1->n)
					{
						dprintf(2, "\t\t\t\t.frames[%zu]: %p\n", j, ptr1->frames + j);
							dprintf(2, "\t\t\t\t\t.filepath: %p | %s\n", ptr1->frames[j].filepath, ptr1->frames[j].filepath);
							dprintf(2, "\t\t\t\t\t.mlx_img: %p\n", ptr1->frames[j].mlx_img);
							dprintf(2, "\t\t\t\t\t.width: %d\n", ptr1->frames[j].width);
							dprintf(2, "\t\t\t\t\t.height: %d\n", ptr1->frames[j].height);
							dprintf(2, "\t\t\t\t\t.addr: %p\n", ptr1->frames[j].addr);
							dprintf(2, "\t\t\t\t\t.bits_per_pixel: %d\n", ptr1->frames[j].bits_per_pixel);
							dprintf(2, "\t\t\t\t\t.line_length: %d\n", ptr1->frames[j].line_length);
							dprintf(2, "\t\t\t\t\t.endian: %d\n", ptr1->frames[j].endian);
						j++;
					}
					if (ptr1->n)
					{
						dprintf(2, "\t\t\t\t.current: %p\n", ptr1->current);
						dprintf(2, "\t\t\t\t.n: %d\n", ptr1->n);
						dprintf(2, "\t\t\t\t.current_frame: %d\n", ptr1->current_frame);
						dprintf(2, "\t\t\t\t.dir: %d\n", ptr1->dir);
						dprintf(2, "\t\t\t\t.attr:\n");
							dprintf(2, "\t\t\t\t\t.frametime: %zu\n", ptr1->attr.frametime);
							dprintf(2, "\t\t\t\t\t.animation: %s\n", elem_type_str(ptr1->attr.animation));
							dprintf(2, "\t\t\t\t\t.damage: %d\n", ptr1->attr.damage);
							dprintf(2, "\t\t\t\t\t.hinder: %f\n", ptr1->attr.hinder);
							dprintf(2, "\t\t\t\t\t.walkable: %d\n", ptr1->attr.walkable);
					}
					ptr1++;
					i++;
				}
				i = 0;
				ptr1 = env->scene.elems[FLOOR];
				while (i < MAX_TEXTURE)
				{
					dprintf(2, "\t\t\t[FLOOR][%zu]: %p\n", i, ptr1);
					j = 0;
					while ((int)j < ptr1->n)
					{
						dprintf(2, "\t\t\t\t.frames[%zu]: %p\n", j, ptr1->frames + j);
							dprintf(2, "\t\t\t\t\t.filepath: %p | %s\n", ptr1->frames[j].filepath, ptr1->frames[j].filepath);
							dprintf(2, "\t\t\t\t\t.mlx_img: %p\n", ptr1->frames[j].mlx_img);
							dprintf(2, "\t\t\t\t\t.width: %d\n", ptr1->frames[j].width);
							dprintf(2, "\t\t\t\t\t.height: %d\n", ptr1->frames[j].height);
							dprintf(2, "\t\t\t\t\t.addr: %p\n", ptr1->frames[j].addr);
							dprintf(2, "\t\t\t\t\t.bits_per_pixel: %d\n", ptr1->frames[j].bits_per_pixel);
							dprintf(2, "\t\t\t\t\t.line_length: %d\n", ptr1->frames[j].line_length);
							dprintf(2, "\t\t\t\t\t.endian: %d\n", ptr1->frames[j].endian);
						j++;
					}
					if (ptr1->n)
					{
						dprintf(2, "\t\t\t\t.current: %p\n", ptr1->current);
						dprintf(2, "\t\t\t\t.n: %d\n", ptr1->n);
						dprintf(2, "\t\t\t\t.current_frame: %d\n", ptr1->current_frame);
						dprintf(2, "\t\t\t\t.dir: %d\n", ptr1->dir);
						dprintf(2, "\t\t\t\t.attr:\n");
							dprintf(2, "\t\t\t\t\t.frametime: %zu\n", ptr1->attr.frametime);
							dprintf(2, "\t\t\t\t\t.animation: %s\n", elem_type_str(ptr1->attr.animation));
							dprintf(2, "\t\t\t\t\t.damage: %d\n", ptr1->attr.damage);
							dprintf(2, "\t\t\t\t\t.hinder: %f\n", ptr1->attr.hinder);
							dprintf(2, "\t\t\t\t\t.walkable: %d\n", ptr1->attr.walkable);
					}
					ptr1++;
					i++;
				}
				dprintf(2, "\t\t\t[PORTAL]: %p\n", env->scene.elems[PORTAL]);
				i = 0;
				ptr1 = env->scene.elems[PORTAL];
				
				dprintf(2, "\t\t\t[PORTAL][%zu]: %p\n", i, ptr1);
				j = 0;
				while ((int)j < ptr1->n)
				{
					dprintf(2, "\t\t\t\t.frames[%zu]: %p\n", j, ptr1->frames + j);
						dprintf(2, "\t\t\t\t\t.filepath: %p | %s\n", ptr1->frames[j].filepath, ptr1->frames[j].filepath);
						dprintf(2, "\t\t\t\t\t.mlx_img: %p\n", ptr1->frames[j].mlx_img);
						dprintf(2, "\t\t\t\t\t.width: %d\n", ptr1->frames[j].width);
						dprintf(2, "\t\t\t\t\t.height: %d\n", ptr1->frames[j].height);
						dprintf(2, "\t\t\t\t\t.addr: %p\n", ptr1->frames[j].addr);
						dprintf(2, "\t\t\t\t\t.bits_per_pixel: %d\n", ptr1->frames[j].bits_per_pixel);
						dprintf(2, "\t\t\t\t\t.line_length: %d\n", ptr1->frames[j].line_length);
						dprintf(2, "\t\t\t\t\t.endian: %d\n", ptr1->frames[j].endian);
					j++;
				}
				if (ptr1->n)
				{
					dprintf(2, "\t\t\t\t.current: %p\n", ptr1->current);
					dprintf(2, "\t\t\t\t.n: %d\n", ptr1->n);
					dprintf(2, "\t\t\t\t.current_frame: %d\n", ptr1->current_frame);
					dprintf(2, "\t\t\t\t.dir: %d\n", ptr1->dir);
					dprintf(2, "\t\t\t\t.attr:\n");
						dprintf(2, "\t\t\t\t\t.attr.frametime: %zu\n", ptr1->attr.frametime);
						dprintf(2, "\t\t\t\t\t.attr.animation: %s\n", elem_type_str(ptr1->attr.animation));
						dprintf(2, "\t\t\t\t\t.attr.damage: %d\n", ptr1->attr.damage);
						dprintf(2, "\t\t\t\t\t.attr.hinder: %f\n", ptr1->attr.hinder);
						dprintf(2, "\t\t\t\t\t.attr.walkable: %d\n", ptr1->attr.walkable);
				}
			dprintf(2, "\t\t.map: %p\n", env->scene.map);
			dprintf(2, "\t\t.width: %d\n", env->scene.width);
			dprintf(2, "\t\t.height: %d\n", env->scene.height);
			dprintf(2, "\t\t.portals: %p\n", &env->scene.portals);
				dprintf(2, "\t\t\t.tab: %p\n", env->scene.portals.tab);
				i = 0;
				while ((int)i < env->scene.portals.total)
				{
					dprintf(2, "\t\t\t\t[%zu]: %p\n", i, env->scene.portals.tab + i);
						dprintf(2, "\t\t\t\t\t.id: %d\n", env->scene.portals.tab[i].id);
						dprintf(2, "\t\t\t\t\t.pos: x%d y%d\n", env->scene.portals.tab[i].pos.x, env->scene.portals.tab[i].pos.y);
						dprintf(2, "\t\t\t\t\t.face: %d (%s)\n", env->scene.portals.tab[i].face, portal_face_str(env->scene.portals.tab[i].face));
						dprintf(2, "\t\t\t\t\t.is_open: %d\n", env->scene.portals.tab[i].is_open);
						dprintf(2, "\t\t\t\t\t.linked_portal: %d\n", env->scene.portals.tab[i].linked_portal);
					i++;
				}
				dprintf(2, "\t\t\t.total: %d\n", env->scene.portals.total);
				dprintf(2, "\t\t\t.opened: %p\n", env->scene.portals.opened);
					dprintf(2, "\t\t\t\t[0]: %d\n", env->scene.portals.opened[0]);
					dprintf(2, "\t\t\t\t[1]: %d\n", env->scene.portals.opened[1]);
				dprintf(2, "\t\t\t.opened_count: %d\n", env->scene.portals.opened_count);

		dprintf(2, "\t->mlx: %p\n", env->mlx);
		dprintf(2, "\t->win: %p\n", env->win);
		dprintf(2, "\t->img: %p\n", &env->img);
		dprintf(2, "\t->key_state: %p\n", &env->key_state);
		dprintf(2, "\t->mouse: %p\n", &env->mouse);
		dprintf(2, "\t->player: %p\n", &env->player);
		dprintf(2, "\t->monster: %p\n", &env->monster);
		dprintf(2, "\t->call_mutex: %p\n", &env->call_mutex);
		dprintf(2, "\t->z_buffer: %p\n", env->z_buffer);
		dprintf(2, "\t->entities: %p\n", env->entities);
		dprintf(2, "\t->entity_count: %p\n", &env->entity_count);
		dprintf(2, "\t->frame_time: %p\n", &env->frame_time);
		dprintf(2, "\t->frame_timer: %p\n", &env->frame_timer);
		dprintf(2, "\t->buffer: %p\n", env->buffer);
	dprintf(2, "\nEND MEMORY MAP\n");
}
