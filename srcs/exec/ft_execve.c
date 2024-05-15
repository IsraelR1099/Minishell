/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davidbekic <davidbekic@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 18:41:04 by dbekic            #+#    #+#             */
/*   Updated: 2022/10/30 02:54:13 by davidbekic       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../Libft/libft.h"

static int	ft_is_alias(char *str)
{
	int	i;

	i = 0;
	while (str[i] != 0)
	{
		if (str[i] == '/')
			return (0);
		i++;
	}
	return (1);
}

static int	ft_find_exec(t_env *env, char **names)
{
	char	tstr[BUFFER_SIZE - 1];
	char	*path;
	char	*pstr;
	char	*cpath;

	path = ft_expand(env, "PATH");
	ft_bzero(tstr, BUFFER_SIZE - 1);
	cpath = path;
	if (ft_is_alias(names[0]))
	{
		while (cpath)
		{
			pstr = ft_strchrnul(cpath, ':');
			ft_memcpy(tstr, cpath, pstr - cpath);
			tstr[pstr - cpath] = '/';
			ft_memcpy(tstr + (pstr - cpath) + (pstr > cpath),
				names[0], ft_strlen(names[0]));
			execve(tstr, names, env->envp);
			ft_memset(tstr, 0, BUFFER_SIZE - 1);
			cpath = pstr + 1;
			if (pstr[0] != ':')
				return (127);
		}
	}
	return (0);
}

int	ft_execve(t_env *env, char **names)
{
	int	ret;

	ret = 0;
	if (!ft_is_alias(names[0]) || !ft_expand(env, "PATH"))
		ret = ft_is_file_or_dir(names[0]);
	if (ret)
		return (ret);
	if (!(ft_strcmp(*names, "bash"))
		|| !(ft_strcmp(*names, "./minishell")) || !(ft_strcmp(*names, "zsh")))
	{
		env->envp = ft_create_envp(env);
		if (!env->envp)
			ft_error("malloc error", 1);
	}
	if (ft_is_alias(names[0]) && ft_expand(env, "PATH"))
	{
		ret = ft_find_exec(env, names);
		if (ret)
			ft_printf(2, "minishell: %s: command not found\n", names[0]);
	}
	else
		ret = execve(names[0], names, env->envp) * -1;
	return (ret);
}
