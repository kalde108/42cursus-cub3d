/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_integer.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 02:58:54 by ibertran          #+#    #+#             */
/*   Updated: 2024/01/18 01:16:42 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_INTEGER_H
# define FT_INTEGER_H

char	*ft_itoa_base(int nbr, char *base);
char	*ft_itoa(int n);
char	*ft_uitoa_base(unsigned int nbr, char *base);
char	*ft_ulltoa_base(unsigned long long nbr, char *base);
float	ft_fabs(float x);
int		ft_abs(int x);
int		ft_atoi(const char *nptr);
int		ft_isrange(int c, int start, int end);
int		ft_itoalen_base(int n, char *base);
int		ft_itoalen(int n);
int		ft_strtoi(const char *ptr, char **endptr);
int		ft_uitoalen_base(unsigned int n, char *base);
int		ft_ulltoalen_base(unsigned long long nbr, char *base);
long	ft_strtol(const char *ptr, char **endptr);

#endif //FT_INTEGER_H