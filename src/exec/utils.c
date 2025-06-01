/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosc <abosc@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 23:32:34 by abosc             #+#    #+#             */
/*   Updated: 2025/06/01 07:20:30 by abosc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	dup_close(int fd, int fileno)
{
	dup2(fd, fileno);
	close(fd);
}

void	free_array(char **array)
{
	int	index;

	if (!array)
		return ;
	index = 0;
	while (array[index])
		free(array[index++]);
	free(array);
	return ;
}

void	resetfd(int fd, int fout)
{
	if (fd != -1 && fd != 0 && fd != 1)
	{
		close(fd);
	}
	// Ne pas réassigner fd ici car c'est passé par valeur
	(void)fout; // Éviter le warning unused parameter
}
