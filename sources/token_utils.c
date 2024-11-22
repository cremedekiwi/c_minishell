/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarumuga <jarumuga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 19:37:17 by habernar          #+#    #+#             */
/*   Updated: 2024/10/16 18:12:10 by jarumuga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_isalnumsup(char c)
{
	if (!(c == 0 || c == '(' || c == ')' || c == '>' || c == '<' || c == '&'
			|| c == '|' || c == '\'' || c == '\"'))
		return (true);
	return (false);
}

bool	is_operator(t_toktype type)
{
	return (type >= T_AND && type <= T_PIPE);
}

bool	is_redirection(t_toktype type)
{
	return (type >= T_DSUP && type <= T_SINF);
}
