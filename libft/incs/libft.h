/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 22:07:07 by ibertran          #+#    #+#             */
/*   Updated: 2024/04/19 22:13:56 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

/* INCLUDES *******************************************************************/

# include "ft_char.h"
# include "ft_integer.h"
# include "ft_lst.h"
# include "ft_mem.h"
# include "ft_misc.h"
# include "ft_string.h"
# include "ft_vector.h"

/* MISC FUNCTIONS *************************************************************/

int		ft_close(int *fd);
void	ft_free_array(void **array);
void	ft_free_2darray_char(char **array);
int		get_fd_content(int fd, char **content);
int		get_next_line(int fd, char **line);

/* FT_PRINTF ******************************************************************/

int		ft_dprintf(int fd, const char *str, ...) \
				__attribute__ ((format (printf, 2, 3)));
char	*ft_sprintf(const char *str, ...) \
				__attribute__ ((format (printf, 1, 2)));

#endif //LIBFT_H