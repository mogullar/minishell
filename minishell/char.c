/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaritas <msaritas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 16:43:23 by msaritas          #+#    #+#             */
/*   Updated: 2023/11/06 16:43:24 by msaritas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	printdquote(char *content, int *location)
{
	int	i;

	i = 0;
	while (content[i])
	{
		if (content[i] && content[i] == '\\')
		{
			if (content[i + 1] && content[i + 1] == 'n')
			{
				printf("\n");
				i++;
			}
			else
				printf("%c", content[i]);
		}
		else
			printf("%c", content[i]);
		i++;
	}
	*location = 1;
}
