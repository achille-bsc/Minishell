/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosc <abosc@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 00:11:54 by abosc             #+#    #+#             */
/*   Updated: 2025/03/08 20:45:02 by alegrix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H 

# include <stdio.h>
# include "./structures.h"
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

void	mininours(int argc, char **argv, char **env);

#endif
