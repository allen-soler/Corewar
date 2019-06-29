/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalonso <nalonso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 16:52:20 by nalonso           #+#    #+#             */
/*   Updated: 2019/06/29 15:48:44 by jallen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# define _EOF -1

# include <stdlib.h>

typedef struct		s_garbage
{
	void			**pointers;
	size_t			arr_len;
	size_t			mem_len;
}					t_garbage;

typedef	struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

typedef struct		s_point
{
	int				x;
	int				y;
}					t_point;

int					ft_printf(const char *format, ...);
int					ft_fprintf(int fd, const char *format, ...);

/*
** Libc functions
*/

int					ft_max(int a, int b);
int					ft_strver(char *str, int (f)(int));
void				**realloc_tab(void **ptr, size_t new_size,\
						size_t original_size);
void				*ft_memset(void *b, int c, size_t len);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
size_t				ft_strlen(const char *s);
char				*ft_strdup(const char *s1);
char				*ft_strcpy(char *dst, const char *src);
char				*ft_strncpy(char *dst, const char *src, size_t len);
char				*ft_strcat(char *s1, const char *s2);
char				*ft_strncat(char *s1, const char *s2, size_t n);
size_t				ft_strlcat(char *dst, const char *src, size_t dstsize);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strstr(const char *str, const char *to_find);
char				*ft_strnstr(const char *str, const char *to_f, size_t len);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_atoi(const char *str);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);
char				*ft_strndup(const char *s1, size_t n);
char				*ft_strrnstr(const char *str,\
								const char *to_find, size_t len);
size_t				ft_tab_len(char **tab);
void				ft_free_tab(char **tab);
void				ft_print_tab(char **tab);
int					ft_isquote(char c);
int					ft_isblank(char c);
char				**ft_splitwhite(char const *s);

/*
** Aditional functions
*/

void				*ft_memalloc(size_t size);
void				ft_memdel(void **ap);
char				*ft_strnew(size_t size);
void				ft_strdel(char **as);
void				ft_striter(char *s, void (*f)(char *s));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strsub(char const *s, unsigned int start, size_t n);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s);
char				**ft_strsplit(char const *s, char c);
char				*ft_itoa(int nbr);
void				ft_strclr(char *s);
void				ft_putchar(char c);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr(char *str);
void				ft_putstr_fd(char *str, int fd);
void				ft_putnbr(int nbr);
void				ft_putnbr_fd(int nbr, int fd);
void				ft_putendl(char const *str);
void				ft_putendl_fd(char const *str, int fd);
int					ft_endswith(const char *str, const char *suffix);

/*
** List manipulation
*/

t_list				*ft_lstnew(void const *content, size_t content_size);
void				ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstadd(t_list **alst, t_list *nw);
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));

/*
** Personal Funcions
*/

int					ft_isspace(int c);
void				*ft_realloc(void *ptr, size_t n_size, size_t o_size);
unsigned long		ft_djb2(char *str);

/*
** t_garbage Funcions
*/

t_garbage			gb_init(void);
void				*gb_malloc(t_garbage *gb, size_t size);
void				gb_freeall(t_garbage *gb);

#endif
