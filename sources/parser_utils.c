/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habernar <habernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 22:43:42 by habernar          #+#    #+#             */
/*   Updated: 2024/10/13 19:26:06 by habernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	nothing_to_parse(char *str)
{
	char	*head;

	(void)head;
	if (!str || !*str)
		return (true);
	head = str;
	while (*str && is_whitespace(*str))
		str++;
	return (false);
}

int	is_whitespace(char c)
{
	if (c == ' ' || c == '\n' || c == '\t'
		|| c == '\v' || c == '\r' || c == '\f')
		return (1);
	return (0);
}

int	is_delimiter(char c)
{
	if (c == '(' || c == ')' || c == '&' || c == '|' || c == 0)
		return (1);
	return (0);
}

int	skip_whitespace(char **str)
{
	char	*s;

	s = *str;
	while (*(*str) && (*(*str) == ' ' || *(*str) == '\t'
			|| *(*str) == '\r' || *(*str) == '\n' || *(*str) == '\f'))
	{
		(*str)++;
	}
	return ((int)(*str - s));
}

void	skip_quotes(char **str)
{
	while (*(*str) && !is_delimiter(*(*str)))
	{
		if (*(*str) == '\'')
		{
			(*str)++;
			while (*(*str) && *(*str) != '\'')
				(*str)++;
		}
		if (*(*str) == '\"')
		{
			(*str)++;
			while (*(*str) && *(*str) != '\"')
				(*str)++;
		}
		(*str)++;
	}
}
