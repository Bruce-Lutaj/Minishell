/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chsassi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 16:43:28 by chsassi           #+#    #+#             */
/*   Updated: 2024/09/13 16:43:31 by chsassi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*new_env_node(const char *env_var)
{
	t_env	*new_node;
	char	*equal_sign;
	int		equal_sign_pos;
	char	*new_var;

	equal_sign = ft_strchr(env_var, '=');
	if (!equal_sign)
		return (NULL);
	equal_sign_pos = ft_strlen_until((char *)env_var, '=');
	new_var = (char *)ft_calloc(equal_sign_pos + 1, sizeof(char));
	ft_strlcpy(new_var, env_var, equal_sign_pos + 1);
	new_node = (t_env *)ft_calloc(1, sizeof(t_env));
	if (!new_node)
		return (free(new_var), NULL);
	new_node->var = new_var;
	new_node->content = ft_strdup(equal_sign + 1);
	if (!new_node->content)
		new_node->is_hidden = true;
	else
		new_node->is_hidden = false;
	new_node->next = NULL;
	return (new_node);
}

t_env	*create_envp(char **envp)
{
	t_env	*head;
	t_env	*current = NULL;
	t_env	*new_node = NULL;
	int		rows;

	rows = 0;
	while (envp[rows])
	{
		new_node = new_env_node(envp[rows]);
		if (!new_node)
			return (free(new_node), NULL);
		if (!head)
		{
			head = new_node;
			current = head;
		}
		else
		{
			env_lstadd_back(head, new_node);
			current->next = new_node;
		}
		new_node = new_node->next;
		rows++;
	}
	return (head);
}

// t_env	*find_env_var(t_env *env, char *var)
// {
// 	while (env)
// 	{
// 		if (!ft_strcmp(env->var, var))
// 			return (env);
// 		env = env->next;
// 	}
// 	return (NULL);
// }

// void	update_env_var(t_env *env_list, const char *var_name, const char *new_value)
// {
// 	t_env	*var;

// 	var = find_env_var(env_list, var_name);
// 	if (var)
// 	{
// 		free(var->content);
// 		var->content = ft_strdup(new_value);
// 	}
// }
