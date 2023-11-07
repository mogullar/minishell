/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaritas <msaritas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 15:59:13 by msaritas          #+#    #+#             */
/*   Updated: 2023/11/06 16:42:58 by msaritas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	if_not_n(int n)
{
	if (!n)
		printf("\n");
}

int	if_option(char *option, int *n, int location)
{
	int	j;

	j = 0;
	if (option[0] == '-' && option[1] == 'n')
	{
		j = 2;
		while (option[j] && option[j] == 'n')
			j++;
		if (!option[j] && !location)
		{
			*n = 1;
			return (1);
		}
	}
	return (0);
}

int	echo(t_data *data, t_parser *a)
{
	int	location;
	int	n;
	int	i;

	location = 0;
	n = 0;
	i = 0;
	while (a->commands[++i])
	{
		if (!if_option(a->commands[i], &n, location))
		{
			if (!ft_strcmp(a->commands[i], "-n"))
				printf("-n");
			else
				printdquote(a->commands[i], &location);
			if (a->commands[i + 1])
				printf(" ");
		}
	}
	if_not_n(n);
	data->exit_status = 0;
	return (data->exit_status);
}
