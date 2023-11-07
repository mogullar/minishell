/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaritas <msaritas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 16:35:54 by msaritas          #+#    #+#             */
/*   Updated: 2023/11/06 16:40:35 by msaritas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main_loop_unset(t_data *data, t_append_var **len_strs, int *len,
		char *content)
{
	int		i;
	int		index;
	char	**split;

	i = 0;
	while (content[i] && content[i] != '=')
		i++;
	split = NULL;
	index = -1;
	while (data->envp[++index])
	{
		split = ft_split(data->envp[index], '=');
		if (!content || !content[0])
			return (free_of_unset(data, split, content));
		else if (content[i] == '=' || ft_isdigit(content[0]))
			return (free_of_unset2(data, split, content));
		else if (!ft_strcmp(split[0], content))
		{
			fill_for_strs_unset(data, &len, &len_strs, content);
			break ;
		}
		free_arrays(&split, -1);
	}
	return (ft_free_content(split, content));
}

char	**remove_from_env(t_data *data, int len, t_append_var *len_strs)
{
	char	**new;
	int		i;
	int		j;

	j = -1;
	i = -1;
	while (data->envp[++i])
		;
	new = ft_calloc(i - len + 1, sizeof(char *));
	while (len_strs && len_strs->content)
	{
		i = -1;
		while (data->envp[++i] != NULL)
		{
			data->vars = ft_split(data->envp[i], '=');
			if (ft_strcmp(data->vars[0], len_strs->content))
			{
				new[++j] = malloc(ft_strlen(data->envp[i]) + 1);
				ft_strlcpy(new[j], data->envp[i], ft_strlen(data->envp[i]) + 1);
			}
			free_arrays(&data->vars, -1);
		}
		len_strs = len_strs->next;
	}
	return (new);
}

void	if_exist(t_data *data, int len, t_append_var *tmp,
		t_append_var *len_strs)
{
	char	**tmp2;

	tmp2 = data->envp;
	len_strs = tmp;
	data->envp = remove_from_env(data, len, len_strs);
	len_strs = tmp;
	free_arrays(&tmp2, -1);
}

int	unset(t_data *data, t_parser *a)
{
	t_append_var	*len_strs;
	t_append_var	*tmp;
	int				len;
	int				r;
	int				i;

	len = 0;
	if (a->commands[1] == NULL)
		return (data->exit_status);
	len_strs = ft_calloc(1, sizeof(t_append_var));
	len_strs->next = NULL;
	tmp = len_strs;
	i = 0;
	while (a->commands[++i] != NULL)
		r = main_loop_unset(data, &len_strs, &len, ft_strdup(a->commands[i]));
	if (r == 1)
		if_exist(data, len, tmp, len_strs);
	if (r)
		data->exit_status = 0;
	free_len_strs(len_strs, tmp);
	return (data->exit_status);
}

void	if_only_export(t_data *data, t_parser *a)
{
	if (a->commands[1] == NULL)
	{
		only_export(data);
		data->exit_status = 0;
		return ;
	}
}
