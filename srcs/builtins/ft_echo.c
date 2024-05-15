/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davidbekic <davidbekic@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 11:58:05 by dbekic            #+#    #+#             */
/*   Updated: 2022/10/30 02:52:44 by davidbekic       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../Libft/libft.h"

static	int	ft_check_n_flag(char **names)
{
	unsigned char	n_flag;
	int				no_flag;
	int				i;
	int				j;

	n_flag = 0;
	no_flag = 1;
	i = 0;
	j = 1;
	while (names[++i - 1])
	{
		if ((!(ft_strncmp(names[i - 1], "-n", 2))))
		{
			while (names[i - 1][j])
			{
				if (names[i - 1][++j - 1] != 'n' && (names[i - 1][j + 1] != 0
							|| names[i - 1][j + 1] != 32))
					return (n_flag);
			}
			if (no_flag)
				n_flag++;
		}
		j = 1;
	}
	return (n_flag);
}

int	ft_echo(char **names)
{
	unsigned char	n_flag;

	n_flag = 0;
	n_flag = ft_check_n_flag(names);
	while (*(++names + n_flag))
	{
		if (ft_printf(1, "%s", *(names + n_flag)) < 0)
			return (1);
		if (*(names + 1 + n_flag) != NULL && strlen(*(names + n_flag)))
		{
			if (ft_printf(1, " ") < 0)
				return (1);
		}
	}
	if (!n_flag)
	{
		if (ft_printf(1, "\n") < 0)
			return (1);
	}
	return (0);
}
