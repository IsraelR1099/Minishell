/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbekic <dbekic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 12:17:47 by irifarac          #+#    #+#             */
/*   Updated: 2022/10/31 10:37:28 by dbekic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../Libft/libft.h"

int	g_exit;

int	main(int ac, char **av, char **main_env)
{
	static char		*buf = NULL;
	t_env			*env;

	if (ac > 1)
	{
		ft_printf(2, "too many aruguments\n");
		exit(1);
	}
	if ((ac > 1 && av[0][0] == '&') || !*main_env)
		exit(1);
	env = ft_init_env(main_env);
	buf = (char *)ft_calloc(sizeof(char) * BUFFER_SIZE, 1);
	if (!buf | !env)
		ft_free_env(env, 1);
	ft_main_loop(&buf, &env);
	return (0);
}
