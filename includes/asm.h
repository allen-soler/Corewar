/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jallen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 10:28:18 by jallen            #+#    #+#             */
/*   Updated: 2019/06/27 20:02:58 by bghandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <limits.h>
# include "op.h"
# include "../libft/libft.h"
# define S_BOLD "\e[001m"
# define E_BOLD "\e[0022m"


typedef struct		s_par
{
	char			*param;
	int				type; //1: REG_CODE, 2: DIR_2Bytes, 3: DIR_4Bytes, 4: IND 5: DIR_LAB 6: inst 7: LABEL 8: comment
	struct s_par	*lbl_ptr;
	struct s_par	*next;
}					t_par;

/**
 *		Error handling
**/

void	error_function(char *string, t_par **list);
void	error_custom(char *message, t_par *list);
int		check_comma(char *line, t_par **list);

/**
 *		Handle labels
**/

int		direct_label(t_par **list, char *arg);
int		set_label(char **line, t_par **list);

/**
 *		Structure handling
**/

t_par	*add_parameter(t_par *list, char *inst, int type);
t_par	*next_inst(t_par *list);
void	test_print(t_par *list);//will have to delete when done

/**
 *		Handle strings
**/

char	*skip_space(char *line);
size_t	str_repoint(char *haystack, char *needle);
void	travel_states(char **line, int state);
void	free_2d(char **arrray);

/**
 *		Tokens
**/

char	**instructions_array(void);
void	middlefunction(char **line, int state, t_par **list);
int		name_token(char **line, int state, t_par **list);
int		init_comm_token(char **line, int state, t_par **list);
int		search_valid_inst(char **line, t_par **list);
void	check_args(char **line, t_par **list);
int		check_register(char *arg, t_par **list);
int		check_direct(char *arg, t_par **list);
int		check_indirect(char *arg, t_par **list);

/**
 *		Syntax
**/

void	check_syntax(t_par *list);
int		check_class(int	cur);
t_par	match_instruction(t_par *tmp, char **instructions, t_par *head);
void	fetch_function(t_par *tmp, int class, t_par *head);

t_par	*live_function(t_par *tmp, t_par *head);
t_par	class_7(t_par *tmp, t_par *head);

#endif
