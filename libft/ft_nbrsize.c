/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbrsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 16:52:06 by julnolle          #+#    #+#             */
/*   Updated: 2019/12/19 19:42:59 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_nbrsize(long n)
{
	size_t size;

	if (n == 0)
		size = 1;
	else
	{
		size = (n < 0) ? 1 : 0;
		n = (n < 0) ? -n : n;
		while (n > 0)
		{
			n = n / 10;
			size++;
		}
	}
	return (size);
}