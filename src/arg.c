/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-jesu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 13:32:34 by dde-jesu          #+#    #+#             */
/*   Updated: 2018/12/10 14:21:01 by dde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arg.h"
#include <stdlib.h>

static void	pop_arg(t_farg *arg, va_list ap)
{
	if (arg->type == PTR)
		arg->value.p = va_arg(ap, void *);
	else if (arg->type == INT)
		arg->value.i = va_arg(ap, int);
	else if (arg->type == UINT)
		arg->value.i = va_arg(ap, unsigned int);
	else if (arg->type == LONG)
		arg->value.i = va_arg(ap, long);
	else if (arg->type == ULONG)
		arg->value.i = va_arg(ap, unsigned long);
	else if (arg->type == LLONG)
		arg->value.i = va_arg(ap, long long);
	else if (arg->type == ULLONG)
		arg->value.i = va_arg(ap, unsigned long long);
	else if (arg->type == USIZET)
		arg->value.i = va_arg(ap, ssize_t);
	else if (arg->type == SIZET)
		arg->value.i = va_arg(ap, size_t);
	else if (arg->type == IMAX || arg->type == UIMAX)
		arg->value.i = (arg->type == IMAX ? va_arg(ap, intmax_t)
				: va_arg(ap, uintmax_t));
	else if (arg->type == DBL)
		arg->value.d = va_arg(ap, double);
	else if (arg->type == LDBL)
		arg->value.d = va_arg(ap, long double);
}

int			resolve_arg(t_farg *arg, t_va_slist *ap)
{
	if (arg->type == NONE)
		return (-1);
	if (arg->idx < ap->idx)
		return (0);
	else if (arg->idx == ap->idx)
	{
		pop_arg(arg, ap->ap);
		ap->idx++;
		return (0);
	}
	else
		return (-1);
}

int			get_arg(t_farg *arg, t_types type, t_va_slist *ap)
{
	if (arg->type == NONE)
		arg->type = type;
	if (ap->lock)
		return (-1);
	else if (arg->type != type)
		(void)*((void *)NULL);
	return (resolve_arg(arg, ap));
}

t_farg		*arg_at_index(const t_farg *begin, size_t pos)
{
	if (pos == 0)
		return ((t_farg *)begin);
	while (--pos && begin && begin->next)
		begin = begin->next;
	return (pos ? NULL : begin->next);
}
