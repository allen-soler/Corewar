/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaz <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:33:27 by zaz               #+#    #+#             */
/*   Updated: 2019/05/21 14:26:13 by nalonso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * ** Toutes les tailles sont en octets.
 * ** On part du principe qu'un int fait 32 bits. Est-ce vrai chez vous ?
 * */

#define IND_SIZE2
#define REG_SIZE4
#define DIR_SIZEREG_SIZE


# define REG_CODE1
# define DIR_CODE2
# define IND_CODE3


#define MAX_ARGS_NUMBER4
#define MAX_PLAYERS4
#define MEM_SIZE(4*1024)
#define IDX_MOD(MEM_SIZE / 8)
#define CHAMP_MAX_SIZE(MEM_SIZE / 6)

#define COMMENT_CHAR'#'
#define LABEL_CHAR':'
#define DIRECT_CHAR'%'
#define SEPARATOR_CHAR','

#define LABEL_CHARS"abcdefghijklmnopqrstuvwxyz_0123456789"

#define NAME_CMD_STRING".name"
#define COMMENT_CMD_STRING".comment"

#define REG_NUMBER16

#define CYCLE_TO_DIE1536
#define CYCLE_DELTA50
#define NBR_LIVE21
#define MAX_CHECKS10

/*
 * **
 * */

typedef chart_arg_type;

#define T_REG1
#define T_DIR2
#define T_IND4
#define T_LAB8

/*
 * **
 * */

# define PROG_NAME_LENGTH(128)
# define COMMENT_LENGTH(2048)
# define COREWAR_EXEC_MAGIC0xea83f3

typedef structheader_s
{
	  unsigned intmagic;
	    charprog_name[PROG_NAME_LENGTH + 1];
		  unsigned intprog_size;
		    charprog_namecomment[COMMENT_LENGTH + 1];
}PROG_NAME_LENGTHheader_t;
