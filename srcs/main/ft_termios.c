/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_termios.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbekic <dbekic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 11:39:21 by dbekic            #+#    #+#             */
/*   Updated: 2022/10/28 10:24:39 by dbekic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_free_in_termios(char *buf, t_env *env, char *message)
{
	free(buf);
	ft_free_env(env, 0);
	ft_printf(2, "%s\n", message);
	exit (1);
}

void	ft_termios(char *buf, t_env *env)
{
	struct termios	term;
	struct termios	save_termios;

	if (isatty(STDIN_FILENO) == 0)
		ft_free_in_termios(buf, env, "this is not a tty");
	if (tcgetattr(STDIN_FILENO, &term) < 0)
		ft_free_in_termios(buf, env, "get attributes error");
	save_termios = term;
	term.c_lflag &= ~(ECHOCTL);
	if (tcsetattr(STDIN_FILENO, TCSADRAIN, &term) < 0)
		ft_free_in_termios(buf, env, "set attributes error");
	if (term.c_lflag & (ECHOCTL))
	{
		ft_free_in_termios(buf, env, "attributes wrongly set");
		tcsetattr(STDIN_FILENO, TCSAFLUSH, &save_termios);
	}
}

void	ft_termios_child(void)
{
	struct termios	term;
	struct termios	save_termios;

	if (isatty(STDIN_FILENO) == 0)
		ft_error("this fd is not a tty", 130);
	if (tcgetattr(STDIN_FILENO, &term) < 0)
		ft_error("get attributes error", 130);
	save_termios = term;
	if (tcsetattr(STDIN_FILENO, TCSADRAIN, &term) < 0)
		ft_error("set attributes error", 130);
	if (term.c_lflag == (ECHOCTL))
	{
		tcsetattr(STDIN_FILENO, TCSAFLUSH, &save_termios);
		ft_error("attributes wrongly set", 130);
	}
}
