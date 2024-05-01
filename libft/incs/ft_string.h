/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 16:18:27 by ibertran          #+#    #+#             */
/*   Updated: 2024/04/19 22:14:18 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STRING_H
# define FT_STRING_H

# include "stddef.h"

# define ALPHANUM "abcdefghijklmnopqrstuvwxyz\
ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"

char	*ft_generate_rand_str(size_t len, const char *charset);
char	**ft_split(char const *s, char c);
char	*ft_strchr(const char *s, int c);
char	*ft_strcpy(char *dst, const char *src);
char	*ft_strdup(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strjoin2(char const *s1, char const *s2, char const *s3);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char	*ft_strndup(const char *s, size_t n);
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*ft_strpbrk(const char *str1, const char *str2);
char	*ft_strrchr(const char *s, int c);
char	*ft_strtok(char *str, const char *delimiters);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_countwords(const char *str, const char *sep);
int		ft_isnumber(const char *str);
int		ft_str_in_array(const char *str, const char **array);
int		ft_strcmp(const char *str1, const char *str2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlen_charset(const char *str, const char *charset);
size_t	ft_strlen_protected(const char *str);
size_t	ft_strlen(const char *str);
size_t	ft_strnlen(const char *str, size_t n);
void	ft_free_split_arr(char ***split);
void	ft_striteri(char *s, void (*f)(unsigned int, char*));

#endif //FT_STRING_H
