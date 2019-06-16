/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jallen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 10:28:18 by jallen            #+#    #+#             */
/*   Updated: 2019/06/16 19:01:33 by bghandou         ###   ########.fr       */
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
	int				type; //1: REG_CODE, 2: DIR_CODE, 3: IND_CODE
	struct s_par	*next;
}					t_par;

/**
 *		Structure handling
**/

t_par	*add_parameter(t_par *list, char *inst, int type);
void	test_print(t_par *list);//will have to delete when done

/**
 *		Handle strings
**/

char	*str_repoint(char *haystack, char *needle);
void	travel_states(char **line, int state);

/**
 *		Tokens
**/

void	middlefunction(char **line, int state, t_par *list);
int		name_token(char **line, int state, t_par *list);
int		init_comm_token(char **line, int state, t_par *list);


#endif
