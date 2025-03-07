/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosc <abosc@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 00:20:29 by abosc             #+#    #+#             */
/*   Updated: 2025/03/08 23:56:05 by abosc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H 

typedef struct s_args
{
	char			*arg;
	int				tok;
	char			*name;
	struct s_args	*next;
}				t_args;

typedef struct s_exec
{
	int				fin;
	int				fout;
	struct s_exec	*next;
	t_args			*args;
}				t_exec;

typedef struct s_mnours
{
	int		argc;
	char	**line;
	char	**env;
	int		nb_pipe;
	t_exec	*ex;
	int		act_exec;
}				t_mnours;

# define CMD 11
# define PIP 12
# define OP 13
# define HD 14
# define AP 15
# define TR 16
#endif
