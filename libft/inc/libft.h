/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 10:37:09 by sbruma            #+#    #+#             */
/*   Updated: 2024/12/11 01:53:05 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <strings.h>
# include <stdlib.h>
# include <stdio.h>
# include <stddef.h>
# include <unistd.h>
# include <limits.h>
# include <stdarg.h>
# include <stdbool.h>
# include <fcntl.h>
# include <errno.h>

//ft_is
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_isspace(int c);

//ft_lst
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

//ft_mem
void	ft_bzero(void *s, size_t n);
void	*ft_memset(void *b, int c, size_t len);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t len);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_calloc(size_t count, size_t size);
void	*ft_realloc(void *ptr, size_t old_size, size_t new_size);

//ft_piscine
int		ft_fibonacci(int index);
int		ft_find_next_prime(int nb);
int		ft_is_prime(int nb);
int		ft_iterative_factorial(int nb);
int		ft_iterative_power(int nb, int power);
int		*ft_range(int min, int max);
int		ft_recursive_factorial(int nb);
int		ft_recursive_power(int nb, int power);
int		ft_sqrt(int nb);
void	ft_rev_int_tab(int *tab, int size);
void	ft_sort_int_tab(int *tab, int size);
void	ft_swap(int *a, int *b);
int		ft_ultimate_range(int **range, int min, int max);

//ft_put
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
int		ft_putchar(char c);
int		ft_putstr(char *str);

//ft_str
size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*ft_strncpy(char *dest, const char *src, size_t n);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_strdup(const char *s1);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
size_t	ft_strnlen(const char *s, size_t maxlen);
char	*ft_strcpy(char *dest, const char *src);
char	*ft_strcat(char *dest, const char *src);
char	*ft_strndup(const char *s, size_t n);
int		ft_strcmp(char *s1, char *s2);

//ft_to
int		ft_toupper(int c);
int		ft_tolower(int c);
int		ft_atoi(const char *str);
char	*ft_itoa(int n);
char	*ft_utoa(unsigned long n);
char	*ft_utoa_base(unsigned long value, char *base);
long	ft_atol(const char *str);
long	ft_strtol(const char *str, char **endptr, int base);

#endif