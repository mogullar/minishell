/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaritas <msaritas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 13:28:24 by msaritas          #+#    #+#             */
/*   Updated: 2023/02/15 19:10:35 by msaritas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(int content)
{
	t_list	*a;

	a = (t_list *)malloc(sizeof(content));
	if (!(a))
		return (NULL);
	a -> content = content;
	a -> next = NULL;
	return (a);
}
