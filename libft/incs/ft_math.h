/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_math.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchillon <kchillon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 13:46:52 by kchillon          #+#    #+#             */
/*   Updated: 2024/05/12 13:59:52 by kchillon         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MATH_H
# define FT_MATH_H

# define PI 3.14159265358979323846

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

#endif
