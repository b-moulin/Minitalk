/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoulin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 06:29:36 by bmoulin           #+#    #+#             */
/*   Updated: 2021/07/30 06:29:40 by bmoulin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minitalk.h"

int	ft_atoi(const char *str)
{
	unsigned long long	i;
	short int			k;
	unsigned long		value;

	value = 0;
	k = 1;
	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-')
		k = -k;
	if (str[i] == '+' || str[i] == '-')
		i++;
	else if (!(str[i] >= '0' && str[i] <= '9'))
		return (0);
	if (str[i] >= '0' && str[i] <= '9')
	{
		value = str[i] - 48;
		i++;
		while (str[i] >= '0' && str[i] <= '9')
			value = value * 10 + (str[i++] - 48);
	}
	return (value * k);
}
