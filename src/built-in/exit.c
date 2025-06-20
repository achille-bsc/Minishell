/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosc <abosc@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 21:09:24 by alegrix           #+#    #+#             */
/*   Updated: 2025/06/20 17:03:37 by abosc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	verif_overflow(long long int nb, long long int verif, int sign)
{
	if (sign < 0)
		if (nb == -9223372036854775807 - 1)
			return (0);
	if (nb < verif)
		return (1);
	return (0);
}

int	can_atoll(const char *str)
{
	long long int	nb;
	int				sign;
	long long int	verif;

	sign = 1;
	nb = 0;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		verif = nb;
		nb = nb * 10 + (*str - '0');
		if (verif_overflow(nb, verif, sign))
			return (0);
		str++;
	}
	return (1);
}


int	check_nb(char *line)
{
	int	i;

	i = 0;
	if (line[i] == '-' || line[i] == '+')
		i++;
	while (line[i])
		if (ft_isdigit(line[i++]) == 0)
			return (0);
	if (can_atoll(line) == 0)
		return (0);
	return (1);
}

int	ft_atoll(const char *str)
{
	int				i;
	long long int	nb;
	int				sign;
	int				res;

	if (*str == '\0')
		return (0);
	i = 0;
	sign = 1;
	nb = 0;
	while ((i[str] >= 9 && i[str] <= 13) || i[str] == ' ')
		i++;
	if (i[str] == '+' || i[str] == '-')
	{
		if (i[str] == '-')
			sign *= -1;
		i++;
	}
	while (i[str] >= '0' && i[str] <= '9')
	{
		nb = nb * 10 + (i[str] - '0');
		i++;
	}
	res = (nb * sign) % 256;
	return (res);
}

int	ft_exit(t_mnours *data, char **line)
{
	int	i;

	if (data->nb_pipe < 1)
		ft_dprintf(2, "exit\n");
	if (!line[1])
		return (data->exit = data->exit_status, 0);
	i = 0;
	while (line[1][i])
	{
		if (check_nb(line[1]) == 0)
		{
				data->is_exit = 1;
				ft_dprintf(2, "Mininours: exit: %s: numeric argument required\n", line[1]);
				data->exit = 2;
				return (2);
		}
		i++;
	}
	if (get_array_size(line) > 2)
	{
		ft_dprintf(2, "Mininours: exit: too many arguments\n");
		return (1);
	}
	data->is_exit = 1;
	data->exit = ft_atoll(line[1]);
	return (data->exit);
}
