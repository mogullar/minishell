/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaritas <msaritas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 16:43:06 by msaritas          #+#    #+#             */
/*   Updated: 2023/11/06 16:43:08 by msaritas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*for_var(char **envp, int i)
{
	int	j;
	int	jcopy;
	int	len;

	j = 0;
	len = 0;
	while (envp[i][j] != '=')
		j++;
	jcopy = j + 1;
	while (envp[i][++j])
		len++;
	return (ft_substr(envp[i], jcopy, len));
}

char	*isenv_checker(t_data *data, char *var)
{
	if (!ft_strcmp(var, "?"))
		return (ft_itoa(data->exit_status));
	if (!ft_strcmp(var, "="))
		return ("$=");
	return (NULL);
}

char	*free_isenv(t_data *data, char ***split, char *if_val, int i)
{
	int	j;

	j = -1;
	while ((*split)[++j])
		free((*split)[j]);
	free((*split));
	(*split) = NULL;
	if_val = for_var(data->envp, i);
	return (if_val);
}

char	*isenv(t_data *data, char *var)
{
	char	**split;
	char	*if_val;
	int		i;
	int		j;

	i = -1;
	if_val = NULL;
	if (!ft_strcmp(var, "?") || !ft_strcmp(var, "="))
		return (isenv_checker(data, var));
	while (data->envp[++i] != NULL)
	{
		split = ft_split(data->envp[i], '=');
		if (!ft_strncmp(split[0], var, ft_strlen(split[0]) + 1) && split[1])
			break ;
		j = -1;
		while (split[++j])
			free(split[j]);
		free(split);
		split = NULL;
	}
	if (split == NULL)
		return (NULL);
	else
		if_val = free_isenv(data, &split, if_val, i);
	return (if_val);
}

char	*fordollar2(t_data *data, int *j)
{
	char	*ifvar;
	char	*content;
	char	*val;
	int		i;

	i = (*j) + 1;
	val = NULL;
	content = data->tokens->contents->content;
	if (content && !content[(*j) + 1])
		val = ft_strdup("$");
	else if (content && content[(*j) + 1] == ' ')
		val = ft_strdup("$ ");
	while (content[++(*j)])
	{
		if (check_for_var(content, *j))
			break ;
	}
	if ((*j) == i)
		(*j)++;
	ifvar = ft_substr(content, i, (*j) - i);
	if (val == NULL)
		val = isenv(data, ifvar);
	free(ifvar);
	return (val);
}
