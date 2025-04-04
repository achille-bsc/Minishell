/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosc <abosc@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 00:11:54 by abosc             #+#    #+#             */
/*   Updated: 2025/03/13 23:52:11 by alegrix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H 

# include <sys/wait.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

# include "./structures.h"
# include "../libft/libft.h"

t_env	*ft_envnew(char *line);
char	**parser(char *prompt);

#endif
