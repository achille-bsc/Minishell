/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosc <abosc@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 00:11:54 by abosc             #+#    #+#             */
/*   Updated: 2025/03/09 23:36:39 by abosc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H 

# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

# include "./structures.h"
# include "../libft/libft.h"

char	**parser(char *prompt);

#endif
