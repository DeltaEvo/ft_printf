/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-jesu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 13:30:22 by dde-jesu          #+#    #+#             */
/*   Updated: 2018/12/11 12:04:25 by dde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include <stdint.h>
# include <sys/types.h>
# include "eval.h"

enum					e_pfflags
{
	PF_HASH = 1 << 1,
	PF_ZERO = 1 << 2,
	PF_MINUS = 1 << 3,
	PF_PLUS = 1 << 4,
	PF_SPACE = 1 << 5
};

enum					e_pfelens
{
	PF_H = 1 << 1,
	PF_HH = 1 << 2,
	PF_L = 1 << 3,
	PF_LL = 1 << 4,
	PF_J = 1 << 5,
	PF_Z = 1 << 6,
	PF_LU = 1 << 7
};

# define FIDX(i) ((i) - ' ')
# define LIDX(i) ((i) - 'K')

static enum e_pfflags	g_flags[] =
{
	[FIDX('#')] = PF_HASH,
	[FIDX('0')] = PF_ZERO,
	[FIDX('-')] = PF_MINUS,
	[FIDX('+')] = PF_PLUS,
	[FIDX(' ')] = PF_SPACE,
};

static enum e_pfelens	g_elens[] =
{
	[LIDX('h')] = PF_H,
	[LIDX('l')] = PF_L,
	[LIDX('j')] = PF_J,
	[LIDX('z')] = PF_Z,
	[LIDX('L')] = PF_LU,
};

# define MAX(a,b) ((a) > (b) ? (a) : (b))

typedef struct			s_parse {
	int32_t	param;
	int32_t width;
	int32_t precision;
	int32_t max;
}						t_parse;

t_parse					parse(char **it, t_fmt *f, uint32_t *idx);

#endif
