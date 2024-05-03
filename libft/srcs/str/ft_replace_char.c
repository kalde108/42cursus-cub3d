/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace_char.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 02:37:07 by ibertran          #+#    #+#             */
/*   Updated: 2024/05/02 02:41:09 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

void	ft_replace_char(char *str, const char search, const char replace)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == search)
			str[i] = replace;
		i++;
	}
}
