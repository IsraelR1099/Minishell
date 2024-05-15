/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getcmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davidbekic <davidbekic@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 11:36:23 by dbekic            #+#    #+#             */
/*   Updated: 2022/10/30 02:52:33 by davidbekic       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../Libft/libft.h"

int	ft_getcmd(char **buf, t_env **env)
{
	char	*rl_copy;

	ft_termios(*buf, *env);
	ft_signals();
	rl_copy = readline("🐚 ");
	if (!rl_copy)
	{
		rl_clear_history();
		ft_printf(2, "exit\n");
		free(*buf);
		ft_free_env(*env, 0);
		exit(g_exit);
	}
	add_history(rl_copy);
	ft_memset(*buf, 0, ft_strlen(*buf) + 1);
	ft_memcpy(*buf, rl_copy, ft_strlen(rl_copy) + 1);
	free(rl_copy);
	if (!ft_is_space(*buf))
		g_exit = ft_prompt_parser(buf, *env);
	if (g_exit)
		return (1);
	if (ft_is_builtin(*buf))
		return (ft_run_builtin(env, buf));
	return (1);
}
