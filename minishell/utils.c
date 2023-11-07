/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaritas <msaritas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 15:38:10 by msaritas          #+#    #+#             */
/*   Updated: 2023/11/06 16:11:43 by msaritas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin2(char *s1, char *s2)
{
	char	*total;
	size_t	i;
	size_t	j;

	if (!s1 && !s2)
		return (NULL);
	else if (!s1)
		return ((char *)s2);
	else if (!s2)
		return ((char *)s1);
	i = 0;
	j = 0;
	total = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!total)
		return (NULL);
	while (s1[j])
		total[i++] = s1[j++];
	j = 0;
	while (s2[j])
		total[i++] = s2[j++];
	total[i] = '\0';
	free(s1);
	free(s2);
	return (total);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	if (!s1 || !s2)
		return (1);
	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

t_parser	*ft_lstlast_par(t_parser *lst)
{
	if (!lst)
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

t_parser	*ft_lstnew_parser(void)
{
	t_parser	*a;

	a = ft_calloc(1, sizeof(t_parser));
	if (!(a))
		return (NULL);
	a->in_fd = -1;
	a->out_fd = -1;
	a->hd_fd = -1;
	a->next = NULL;
	return (a);
}

void	ft_lstadd_back_par(t_parser **lst, t_parser *new)
{
	t_parser	*tmp;

	if (!new)
		return ;
	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	tmp = ft_lstlast_par(*lst);
	tmp->next = new;
}
