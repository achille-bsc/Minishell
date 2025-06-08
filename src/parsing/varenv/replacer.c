// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   replacer.c                                         :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: abosc <abosc@student.42lehavre.fr>         +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/05/31 03:50:56 by abosc             #+#    #+#             */
// /*   Updated: 2025/05/31 04:24:31 by abosc            ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../../../headers/minishell.h"

// t_list	*put_in_lst(char **words)
// {
// 	int		i;
// 	t_list	*lst;
// 	t_list	*lst_head;

// 	lst = ft_calloc(sizeof(t_lst), 1);
// 	lst_head = lst;
// 	i = 0;
// 	while (words[i])
// 	{
// 		lst->content = words[i];
// 		if (words[i + 1])
// 		{
// 			lst->next = ft_calloc(sizeof(t_list), 1);
// 			lst = lst->next;
// 		}
// 		i++;
// 	}
// 	return (lst_head);
// }

// int	lst_counter(t_list *lst)
// {
// 	int		count;
// 	t_list	*new_lst;

// 	count = 0;
// 	new_lst = lst;
// 	while (new_lst)
// 	{
// 		count += ft_strlen(new_lst->content);
// 		new_lst = new_lst->next;
// 	}
// 	return (count);
// }

// char	*line_gen(t_list *lst)
// {
// 	int		count;
// 	char	*line;
// 	int		i;
// 	int		j;

// 	i = 0;
// 	j = 0;
// 	count = lst_counter(lst);
// 	line = ft_calloc(sizeof(char), count);
// 	while (lst)
// 	{
// 		ft_strlcat(line, lst->content, ft_strlen(lst->content));
// 		lst = lst->next;
// 	}
// 	return (line);
// }

// char	*replacer(t_mnours *mnours, char *line)
// {
// 	char	*var_name;
// 	char	*new_line;
// 	t_list	*lst;
// 	t_list	*head_lst;
// 	t_env	*env_val;

// 	lst = put_in_lst(ft_split(line, ' '));
// 	head_lst = lst;
// 	while (lst)
// 	{
// 		var_name = ft_strchr(lst->content, '$');
// 		if (var_name != NULL)
// 		{
// 			var_name++;
// 			ft_printf("varname: %s\n", var_name);
// 			env_val = get_env(mnours, var_name);
// 			ft_printf("envval: %s\n", env_val);
// 			free(lst->content);
// 			if (!env_val)
// 				lst->content = "";
// 			else
// 				lst->content = env_val->value;
// 		}
// 		ft_printf("%s\n", lst->content);
// 		lst = lst->next;
// 	}
// 	new_line = line_gen(head_lst);
// 	return (new_line);
// }
