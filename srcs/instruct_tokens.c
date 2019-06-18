/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruct_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bghandou <bghandou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 20:56:35 by bghandou          #+#    #+#             */
/*   Updated: 2019/06/18 20:33:47 by bghandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "asm.h"

char	**instructions_array(void)
{
	char 		**instructions;//can maybe have this as enum

	instructions = ft_strsplit("ld st live add sub and or xor zjmp ldi sti \
lld lldi lfork fork aff", ' ');
	return (instructions);
}

