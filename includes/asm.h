/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jallen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 10:28:18 by jallen            #+#    #+#             */
/*   Updated: 2019/06/12 16:22:04 by bghandou         ###   ########.fr       */
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

char	*str_repoint(char *haystack, char *needle);

typedef struct		s_par
{
	char			*param;
	int				type;
	struct s_par	*next;
}					t_par;

#endif
