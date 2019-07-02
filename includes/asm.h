/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jallen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 10:28:18 by jallen            #+#    #+#             */
/*   Updated: 2019/07/01 16:34:22 by jallen           ###   ########.fr       */
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
# include "../libft/includes/libft.h"
# define S_BOLD "\e[001m"
# define E_BOLD "\e[0022m"
# define RRR 0b01010100
# define RIR 0b01110100
# define RDR 0b01100100
# define IRR 0b11010100
# define IIR 0b11110100
# define IDR 0b11100100
# define DRR 0b10010100
# define DIR 0b10110100
# define DDR 0b10100100
# define RDD 0b01101000
# define IR 0b11010000
# define DR 0b10010000

typedef struct		s_par
{
	char			*param;
	int				type; //1: REG_CODE, 2: DIR_2Bytes, 3: DIR_4Bytes, 4: IND 5: DIR_LAB 6: inst 7: LABEL 8: comment
	struct s_par	*lbl_ptr;
	struct s_par	*next;
}					t_par;

t_op				op_tab[17];

void	readfile(int fd, char **line);
void	to_binary(t_par *lst, char *src, header_t *h);
void	ingest_file(t_par **list, char *file);

/**
*		Error handling
**/

void	error_function(char *string, t_par **list);
void	error_custom(char *message, t_par *list);

/**
 *		Handle labels
**/

int		direct_label(t_par **list, char *arg, int type);
int		set_label(char **line, t_par **list);
int		search_label(char *param, t_par *tmp);
void	match_labels(t_par *tmp, t_par *head);

/**
 *		Structure handling
**/

t_par	*add_parameter(t_par *list, char *inst, int type);
t_par	*next_inst(t_par *list);
int		remaining_tokens(t_par *tmp);
void	test_print(t_par *list);//will have to delete when done

/**
 *		Handle strings
**/

char	*skip_space(char *line);
int		check_comma(char *line, t_par **list);
size_t	str_repoint(char *haystack, char *needle);
void	travel_states(char **line, int state);
void	free_2d(char **arrray);
char	*ignore_hash_comment(char *line);

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
void	match_instruction(t_par *tmp, char **instructions, t_par *head);
t_par	*fetch_function(t_par *tmp, int class, t_par *head);
t_par	*convert_size_direct(t_par *list);
t_par	*class_1(t_par *tmp, t_par *head);
t_par	*class_2(t_par *tmp, t_par *head);
t_par	*class_3(t_par *tmp, t_par *head);
t_par	*class_4(t_par *tmp, t_par *head);
t_par	*class_5(t_par *tmp, t_par *head);
t_par	*class_6(t_par *tmp, t_par *head);
t_par	*class_7(t_par *tmp, t_par *head);
t_par	*class_8(t_par *tmp, t_par *head);
t_par	*class_9(t_par *tmp, t_par *head);


int		to_bin(char	*bin);
void	nb_inst(t_par **lst);
void	encoding(t_par *lst, int fd);

#endif
