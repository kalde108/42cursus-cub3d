/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_math.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchillon <kchillon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 13:46:52 by kchillon          #+#    #+#             */
/*   Updated: 2024/05/30 15:45:32 by kchillon         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MATH_H
# define FT_MATH_H

# define PI 3.14159265358979323846
# define PI_2 1.57079632679489661923
# define SQRT2 1.41421356237309504880
# define SQRT2_2 0.70710678118654752440

typedef struct s_v2d_d
{
	double	x;
	double	y;
}	t_v2d_d;

typedef struct s_v2d_i
{
	int	x;
	int	y;
}	t_v2d_i;

typedef t_v2d_d	t_vertex;

typedef struct s_line
{
	t_vertex	start;
	t_vertex	end;
}	t_line;

typedef struct s_triangle
{
	t_vertex	v1;
	t_vertex	v2;
	t_vertex	v3;
}	t_triangle;

double	ft_euclidean_dist(t_v2d_d a, t_v2d_d b);
void	ft_rotate_v1(double *x, double angle);
void	ft_rotate_v2(t_v2d_d *v, double angle);

#endif
