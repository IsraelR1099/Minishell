/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbekic <dbekic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 16:32:49 by dbekic            #+#    #+#             */
/*   Updated: 2022/10/31 09:59:26 by dbekic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../Libft/libft.h"

static int	ft_update_ex_var(char *key_value, int value_start, t_env *elem)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (elem->value)
		free(elem->value);
	elem->value = NULL;
	if ((key_value[value_start - 1]) != 0)
	{
		elem->value = malloc((ft_strlen(key_value) - value_start) + 1);
		if (!elem->value)
			return (-1);
	}
	else
		return (0);
	while (key_value[value_start + j] != 0)
	{
		i++;
		if (key_value[value_start + i - 1] != '\''
			&& key_value[value_start + i - 1] != '\"' )
			elem->value[++j - 1] = key_value[value_start + i - 1];
	}
	elem->value[j] = 0;
	return (0);
}

int	ft_update_var(char *key_value, int value_start, t_env **env)
{
	t_env	*elem;
	t_env	*aux;
	char	key[BUFFER_SIZE - 1];

	aux = *env;
	ft_bzero(key, BUFFER_SIZE - 1);
	ft_memcpy(key, key_value, value_start - 1);
	key[ft_strlen(key)] = 0;
	elem = ft_find_elem(*env, key);
	if (ft_strcmp((*env)->next->key, "_") == 0)
		return (0);
	if (!elem)
	{
		elem = ft_create_elem(elem, key_value, value_start);
		if (!elem)
			return (-1);
		aux = (*env)->next;
		(*env)->next = elem;
		elem->next = aux;
	}
	else
		return (ft_update_ex_var(key_value, value_start, elem));
	return (0);
}

static int	ft_options(char *str)
{
	if (str[0] == '-')
	{
		ft_printf(2, "minishell: export: options not implemented\n");
		return (2);
	}
	return (0);
}

int	ft_export(char **names, t_env **env)
{
	short	ret;
	short	name;

	ret = 0;
	if (!names[1])
		ft_alphabetic_env(*env);
	else if (ft_options(names[1]))
		return (2);
	while (*++names || ft_strlen(*names))
	{
		if (ft_strlen(*names) > 600)
		{
			ft_printf(2, "too long variable name or value\n");
			return (1);
		}
		name = ft_var_name_check(*names, ft_find_value(*(names)) - 1);
		if (name)
		{
			ret = 1;
			ft_printf(2, "export: `%s': not a valid identifier\n", *names);
		}
		else if (!name)
			g_exit = ft_update_var(*names, ft_find_value(*names), env);
	}
	return (ret);
}
