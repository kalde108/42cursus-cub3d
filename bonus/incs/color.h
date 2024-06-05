#ifndef COLOR_H
# define COLOR_H

# include <stdint.h>

typedef union s_color
{
	uint32_t	argb;
	struct
	{
		uint8_t		b;
		uint8_t		g;
		uint8_t		r;
		uint8_t		a;
	};
}	t_color;

#endif
