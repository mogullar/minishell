/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaritas <msaritas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 16:43:19 by msaritas          #+#    #+#             */
/*   Updated: 2023/11/06 16:43:20 by msaritas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quotecount(t_data *data)
{
	int	qcount;
	int	i;
	int	ifmatch;
	int	ifmatch2;

	i = -1;
	qcount = 0;
	ifmatch = 0;
	ifmatch2 = 0;
	while (data->command_line[++i])
	{
		if (data->command_line[i] == '\"' && ifmatch2 == 0)
			ifmatch = !ifmatch;
		else if (data->command_line[i] == '\'' && ifmatch == 0)
		{
			ifmatch2 = !ifmatch2;
			qcount++;
		}
	}
	return (qcount);
}

int	dquotecount(t_data *data)
{
	int	dqcount;
	int	i;
	int	ifmatch;
	int	ifmatch2;

	i = -1;
	dqcount = 0;
	ifmatch = 0;
	ifmatch2 = 0;
	while (data->command_line[++i])
	{
		if (data->command_line[i] == '\'' && ifmatch2 == 0)
			ifmatch = !ifmatch;
		else if (data->command_line[i] == '\"' && ifmatch == 0)
		{
			ifmatch2 = !ifmatch2;
			dqcount++;
		}
	}
	return (dqcount);
}
