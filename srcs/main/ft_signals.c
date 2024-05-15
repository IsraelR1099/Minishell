/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbekic <dbekic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 11:30:38 by irifarac          #+#    #+#             */
/*   Updated: 2022/10/31 10:02:54 by dbekic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <signal.h>
#include <termios.h>
#include "../../Libft/libft.h"

void	ft_signals(void)
{
	struct sigaction	act;
	struct sigaction	oact;

	act.sa_handler = SIG_DFL;
	ft_memset(&act, 0, sizeof(act));
	act.sa_mask = 0;
	act.sa_flags = SA_RESTART | SA_SIGINFO;
	act.sa_sigaction = ft_info_handler;
	if (sigaction(SIGINT, &act, &oact) < 0)
		ft_error("sigaction error", 130);
	if (sigaction(SIGQUIT, &act, &oact) < 0)
		ft_error("sigaction error", 130);
	if (sigaction(SIGUSR1, &act, &oact) < 0)
		ft_error("sigaction error", 130);
	if (sigaction(SIGUSR2, &act, &oact) < 0)
		ft_error("sigaction error", 130);
	if (sigaction(SIGTTOU, &act, &oact) < 0)
		ft_error("sigaction error", 130);
	if (sigaction(SIGTTIN, &act, &oact) < 0)
		ft_error("sigaction error", 130);
	signal(SIGUSR3, ft_ssh);
	signal(SIGUSR4, ft_ssh);
}

void	ft_state_one(int signo)
{
	if (signo == SIGINT)
	{
		g_exit = 1;
		write(2, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (signo == SIGQUIT)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	ft_state_two(int signo, int status)
{
	if (signo == SIGQUIT)
	{
		write(2, "Quit: 3\n", 8);
		g_exit = 128 + status;
		kill(0, SIGINT);
	}
	else if (signo == SIGINT && g_exit != 131)
		g_exit = 128 + status;
}

void	ft_info_handler(int signo, siginfo_t *info, void *context)
{
	static int	state;
	int			status;

	(void)context;
	status = info->si_status;
	if (status == 258)
	{
		g_exit = status;
		return ;
	}
	if (signo == SIGUSR1)
		state = 1;
	else if (signo == SIGUSR2)
		state = 0;
	if (state == 0)
		ft_state_one(signo);
	if (state == 1)
		ft_state_two(signo, status);
}
