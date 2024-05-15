/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main_loop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbekic <dbekic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 11:46:03 by dbekic            #+#    #+#             */
/*   Updated: 2022/10/31 09:55:31 by dbekic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_main_loop(char **buf, t_env **env)
{
	int	pid;

	while (ft_getcmd(buf, env) >= 0)
	{
		if (ft_is_builtin(*buf) || ft_is_space(*buf))
			continue ;
		pid = fork();
		if (!pid)
		{
			kill(0, SIGUSR1);
			ft_termios_child();
			ft_runcmd(ft_parsecmd(*buf), *env);
		}
		wait(&pid);
		kill(0, SIGUSR2);
		if (WIFEXITED(pid))
			g_exit = WEXITSTATUS(pid);
	}
}
