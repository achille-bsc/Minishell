/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosc <abosc@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 23:32:34 by abosc             #+#    #+#             */
/*   Updated: 2025/06/13 01:27:04 by alegrix          ###   ########.fr       */
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
/*
void	resetfd(int fd, int fout)
{
	if (fd != -1 && fd != 0 && fd != 1)
	{
		close(fd);
	}
	if (fout == 1)
		// Ne pas réassigner fd ici car c'est passé par valeur
		(void)fout; // Éviter le warning unused parameter
}*/

void	resetfd(int fd, int fout)
{
	if (fout == 0 && fd > 2)
	{
		close(fd);
		fd = 0; // Réinitialiser fd à 0 si fout est 0
	}
	if (fout == 1 && fd > 2)
	{
		close(fd);
		fd = 1;
	}
}
