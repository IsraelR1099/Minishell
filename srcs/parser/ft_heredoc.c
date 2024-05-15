/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbekic <dbekic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 14:05:05 by irifarac          #+#    #+#             */
/*   Updated: 2022/10/31 10:00:05 by dbekic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../Libft/libft.h"

static int	ft_getbuf(char **buf, char *delimit)
{
	*buf = readline("> ");
	if (!*buf)
	{
		close(3);
		unlink(".tmp");
		ft_error("here document at line 1 delimited by end-of-file\n", 0);
	}
	if (ft_strncmp(*buf, delimit, ft_strlen(*buf)) == 0)
		return (-1);
	return (0);
}

void	ft_heredoc(t_cmd *cmd, t_env *env)
{
	char			*buf;
	t_doredir		*redircmd;

	redircmd = (t_doredir *)cmd;
	if ((open(".tmp", redircmd->right, 0600)) < 0)
		ft_error("open error", 1);
	while (ft_getbuf(&buf, redircmd->file) >= 0)
	{
		if ((write(3, buf, ft_strlen(buf)) < 0))
			ft_error("write error", 1);
		if ((write(3, "\n", 1) < 0))
			ft_error("write error", 1);
	}
	if ((open(".tmp", O_RDONLY)) < 0)
		ft_error("open error", 1);
	close(3),
	unlink(".tmp");
	dup2(4, 0);
	close(4);
	free(buf);
	ft_runcmd(redircmd->cmd, env);
}
