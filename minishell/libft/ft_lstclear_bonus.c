/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaritas <msaritas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 17:09:00 by msaritas          #+#    #+#             */
/*   Updated: 2022/10/14 19:00:05 by msaritas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*a;

	if (!del || !lst)
		return ;
	while (*lst && lst)
	{
		a = (*lst)-> next;
		ft_lstdelone(*lst, del);
		*lst = a;
	}
	*lst = 0;
}
