/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaritas <msaritas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 16:41:06 by msaritas          #+#    #+#             */
/*   Updated: 2023/11/06 18:44:15 by msaritas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	only_export(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	while (data->envp[++i])
	{
		printf("declare -x ");
		j = 0;
		while (data->envp[i][j] && data->envp[i][j] != '=')
			printf("%c", data->envp[i][j++]);
		if (data->envp[i][j] == '=')
		{
			printf("%c\"", data->envp[i][j++]);
			if (data->envp[i][j] == '$')
				printf("\\");
			while (data->envp[i][j])
				printf("%c", data->envp[i][j++]);
			printf("\"\n");
		}
		else
			printf("\n");
	}
}

void	if_var_exist_control(t_data *data, char **content, int i, int k)
{
	char	*for_error;
	int		j;

	j = i + 1;
	while ((*content)[i] && (*content)[i] != '$')
		i++;
	for_error = ft_substr(*content, j, i - 1);
	while ((*content)[i] && (*content)[i] == '$')
	{
		for_error = ft_strjoin2(for_error, fordollar2(data, &i));
		k = 1;
	}
	if (k == 1)
	{
		ft_putstr_fd("minishell: export: '=", 2);
		ft_putstr_fd(for_error, 2);
	}
	else
	{
		ft_putstr_fd("minishell: export: '", 2);
		ft_putstr_fd(*content, 2);
	}
	ft_putstr_fd("': not a valid identifier\n", 2);
	data->exit_status = 1;
	free(for_error);
}

int	if_var_exist(t_data *data, char **content, char ***content_val, int index)
{
	int	i;
	int	k;
	int	cntrol;

	cntrol = 0;
	i = -1;
	k = 0;
	data->vars = fill_vars(data->envp[index]);
	while ((*content)[++i])
	{
		if ((*content)[i] == '=')
			break ;
	}
	if ((*content)[0] == '=')
	{
		if_var_exist_control(data, content, i, k);
		cntrol = 2;
	}
	else if (!ft_strcmp(data->vars[0], (*content_val)[0]))
		cntrol = 1;
	return (cntrol);
}

void	fill_env(t_data *data, int len, t_append_var *tmp,
		t_append_var *len_strs)
{
	char	**new_env;
	int		i;

	i = 0;
	while (data->envp[i])
		i++;
	new_env = ft_calloc((i + len + 1), sizeof(char *));
	i = -1;
	while (data->envp[++i] != NULL)
	{
		new_env[i] = ft_calloc(ft_strlen(data->envp[i]) + 1, 1);
		ft_strlcpy(new_env[i], data->envp[i], ft_strlen(data->envp[i]) + 1);
	}
	len_strs = tmp;
	while (len_strs && len_strs->content)
	{
		new_env[i] = ft_calloc(ft_strlen(len_strs->content) + 1, 1);
		ft_strlcpy(new_env[i], len_strs->content, ft_strlen(len_strs->content)
			+ 1);
		len_strs = len_strs->next;
		i++;
	}
	free_arrays(&data->envp, -1);
	data->envp = new_env;
}

void	fill_for_strs(t_data *data, int ***len, t_append_var ****len_strs,
		char *content)
{
	int	i;

	i = find_index(content, &i);
	if (ft_isdigit(content[0]) || !ft_isalnum_str(content, i))
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(content, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		data->exit_status = 1;
		return ;
	}
	(***len)++;
	if (!(***len_strs))
		(***len_strs) = ft_calloc(1, sizeof(t_append_var));
	(***len_strs)->content = ft_calloc(ft_strlen(content) + 1, 1);
	ft_strlcpy((***len_strs)->content, content, ft_strlen(content) + 1);
	(***len_strs)->next = NULL;
	(***len_strs) = (***len_strs)->next;
}
