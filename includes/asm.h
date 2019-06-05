/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jallen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 10:28:18 by jallen            #+#    #+#             */
/*   Updated: 2019/06/05 09:05:06 by bghandou         ###   ########.fr       */
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
# include "libft.h"
# define S_BOLD "\e[001m"
# define E_BOLD "\e[0022m"

typedef enum	e_lex
{
				name1, name2, name3, comment1, comment2, comment3,
				instructions, reg1, reg2
}				t_lex;

char	*str_repoint(char *haystack, char *needle);

#endif
