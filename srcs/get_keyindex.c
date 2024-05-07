#include "key_index.h"

#include <X11/Xutil.h>

int	get_keyindex(int keycode)
{
	static const int	code_to_key[KEY_LAST] = {XK_a, XK_b, XK_c, XK_d, XK_e, \
								XK_f, XK_g, XK_h, XK_i, XK_j, XK_k, XK_l, \
								XK_m, XK_n, XK_o, XK_p, XK_q, XK_r, XK_s, \
								XK_t, XK_u, XK_v, XK_w, XK_x, XK_y, XK_z, \
								XK_0, XK_1, XK_2, XK_3, XK_4, XK_5, XK_6, \
								XK_7, XK_8, XK_9, XK_Escape, XK_space, \
								XK_Left, XK_Up, XK_Right, XK_Down, XK_plus, \
								XK_minus};
	size_t				i;

	i = 0;
	while (i < KEY_LAST)
	{
		if (keycode == code_to_key[i])
			return (i);
		i++;
	}
	return (-1);
}
