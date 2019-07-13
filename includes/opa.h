/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opa.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jallen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/13 12:10:12 by jallen            #+#    #+#             */
/*   Updated: 2019/07/13 12:12:18 by jallen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPA_H
# define OPA_H

/*
** Testing out typedefs
*/

# define END_LINE '\0'
# define NEWLINE '\n'
# define SPACE ' '
# define QUOTE '"'
# define REG "r"
# define DIG "0123456789"

/*
** Toutes les tailles sont en octets.
** On part du principe qu'un int fait 32 bits. Est-ce vrai chez vous ?
*/

# define IND_SIZE 2
# define REG_SIZE 4
# define DIR_SIZE REG_SIZE

# define REG_CODE 1
# define DIR_CODE 2
# define IND_CODE 3

# define MAX_ARGS_NUMBER 4
# define MAX_PLAYERS 4
# define MEM_SIZE (4 * 1024)
# define IDX_MOD (MEM_SIZE / 8)
# define CHAMP_MAX_SIZE (MEM_SIZE / 6)

# define COMMENT_CHAR '#'
# define LABEL_CHAR ':'
# define DIRECT_CHAR '%'
# define SEPARATOR_CHAR ','

# define LABEL_CHARS "abcdefghijklmnopqrstuvwxyz_0123456789"

# define NAME_CMD_STRING ".name"
# define COMMENT_CMD_STRING ".comment"

# define REG_NUMBER 16

# define CYCLE_TO_DIE 1536
# define CYCLE_DELTA 50
# define NBR_LIVE 21
# define MAX_CHECKS 10

# define T_REG 1
# define T_DIR 2
# define T_IND 4
# define T_LAB 8

# define PROG_NAME_LENGTH (128)
# define COMMENT_LENGTH (2048)
# define COREWAR_EXEC_MAGIC 0xea83f3

typedef char		t_arg_type;

typedef struct		s_inst
{
	unsigned char	tab[CHAMP_MAX_SIZE + 1];
	int				size;
	int				param_steps;
}					t_inst;

typedef struct		s_header
{
	unsigned int	magic;
	char			prog_name[PROG_NAME_LENGTH + 1];
	unsigned int	prog_size;
	char			comment[COMMENT_LENGTH + 17];
}					t_header;

typedef struct		s_op
{
	char			*name;
	int				param_nb;
	int				param_possible[3];
	int				op_code;
	int				nb_cycle;
	char			*complete_name;
	int				encoding_byte;
	int				direct_size;
}					t_op;

#endif
