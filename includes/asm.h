/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jallen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 10:28:18 by jallen            #+#    #+#             */
/*   Updated: 2019/07/09 12:32:47 by bghandou         ###   ########.fr       */
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
	int				type; //1: REG_CODE, 2: DIR_2Bytes, 3: DIR_4Bytes, 4: IND 5: DIR_LAB4_bytes 6: inst 7: LABEL 8: comment 9: IND_LAB 15: DIR_LAB2Bytes
	int				row;
	struct s_par	*lbl_ptr;
	struct s_par	*next;
}					t_par;

/**
 *		Error handling
**/

void	error_function(char *string, t_par **list);
void	error_custom(char *message, t_par *list);
void	error_state(int state, int row);
void	error_row(char *message, int row);

/**
 *		Handle labels
**/

int		direct_label(t_par **list, char *arg, int type, int row);
int		set_label(char **line, t_par **list, int row);
t_par	*search_label(t_par *to_label, t_par *tmp, int *count);
void	match_labels(t_par *tmp, t_par *head);

/**
 *		Structure handling
**/

t_par	*add_parameter(t_par *list, char *inst, int type, int row);
t_par	*next_inst(t_par *list);
int		remaining_tokens(t_par *tmp);
void	test_print(t_par *list);//will have to delete when done

/**
 *		Handle strings
**/

char	*skip_space(char *line);
int		check_comma(char *line, int row);
size_t	str_repoint(char *haystack, char *needle);
void	travel_states(char **line, int state);
char	*ignore_hash_comment(char *line);

/**
 *		Tokens
**/

char	**instructions_array(void);
int		middlefunction(char **line, int state, t_par **list, int row);
int		name_token(char **line, int state, t_par **list, int row);
int		init_comm_token(char **line, int state, t_par **list, int row);
int		search_valid_inst(char **line, t_par **list, int row);
void	check_args(char **line, t_par **list, int row);
int		check_register(char *arg, t_par **list, int row);
int		check_direct(char *arg, t_par **list, int row);
int		check_indirect(char *arg, t_par **list, int row);

/**
 *		Syntax
**/

void	check_syntax(t_par *list);
int		check_class(int	cur);
void	match_instruction(t_par *tmp, char **instructions);
t_par	*fetch_function(t_par *tmp, int group);
t_par	*convert_size_direct(t_par *list);
t_par	*class_1(t_par *tmp);
t_par	*class_2(t_par *tmp);
t_par	*class_3(t_par *tmp);
t_par	*class_4(t_par *tmp);
t_par	*class_5(t_par *tmp);
t_par	*class_6(t_par *tmp);
t_par	*class_7(t_par *tmp);
t_par	*class_8(t_par *tmp);
t_par	*class_9(t_par *tmp);


#endif
