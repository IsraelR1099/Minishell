/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davidbekic <davidbekic@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 17:09:38 by dbekic            #+#    #+#             */
/*   Updated: 2024/05/15 10:18:40 by irifarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../Libft/libft.h"

static int	ft_is_file_or_no_oldpwd_or_no_home(char **names, t_env *env)
{
	if (names[1] && ft_is_file(names[1]))
	{
		ft_printf(2, "minishell: cd: %s: Not a directory\n", names[1]);
		return (1);
	}
	if (!ft_strlen(ft_expand(env, "OLDPWD"))
		&& !ft_strncmp(names[1], "--", ft_strlen(names[1])))
	{
		ft_printf(2, "minishell: cd: OLDPWD not set\n");
		return (1);
	}
	if (!(*(names + 1)) && !ft_expand(env, "HOME"))
	{
		ft_printf(2, "minishell: cd: HOME not set\n");
		return (1);
	}
	return (0);
}

static void	ft_update_both_vars(t_env *env, char strs[3][BUFFER_SIZE])
{
	ft_update_var(strs[1], 4, &env);
	ft_update_var(strs[0], 7, &env);
}

int	ft_cd(t_env *env, char **names)
{
	char	strs[3][BUFFER_SIZE];
	int		ret;

	ft_memcpy(strs[1], "PWD=", 5);
	ft_memcpy(strs[0], "OLDPWD=", 8);
	ft_memcpy(strs[0] + 7, getcwd(strs[2], BUFFER_SIZE),
		ft_strlen(getcwd(strs[2], BUFFER_SIZE)) + 1);
	if (ft_is_file_or_no_oldpwd_or_no_home(names, env))
		return (1);
	if ((!(ft_strncmp(*(names + 1), "--", ft_strlen(*(names + 1))))))
	{
		ret = chdir((ft_expand(env, "OLDPWD")));
		ft_printf(1, "%s\n", getcwd(strs[2], BUFFER_SIZE));
	}
	else if (!(*(names + 1)))
		ret = chdir(ft_expand(env, "HOME"));
	else
		ret = chdir (*(names + 1));
	if (ret == -1)
		ft_printf(2, "minishell: cd: %s: No such file or directory\n",
			*(names + 1));
	ft_memcpy(strs[1] + 4, getcwd(strs[2], BUFFER_SIZE),
		ft_strlen(getcwd(strs[2], BUFFER_SIZE)) + 1);
	ft_update_both_vars(env, strs);
	return (ret * -1);
}
