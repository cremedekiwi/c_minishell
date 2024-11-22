/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habernar <habernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 22:46:04 by habernar          #+#    #+#             */
/*   Updated: 2024/10/09 21:46:24 by habernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strndup(char *str, int len)
{
	char	*ret;
	char	*head;

	if (len == 0)
		return (0);
	ret = (char *)malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (0);
	head = ret;
	while (*str && len--)
		*ret++ = *str++;
	*ret = 0;
	return (head);
}

char	*ft_strjoin_slash(char *s1, char *s2, char sep)
{
	char	*ret;
	char	*head;

	ret = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	if (!ret)
		return (0);
	head = ret;
	while (*s1)
		*ret++ = *s1++;
	*ret++ = sep;
	while (*s2)
		*ret++ = *s2++;
	*ret = 0;
	return (head);
}

int	only_capital_letter(char *str)
{
	int	i;

	i = 0;
	while (*(str + i) && !is_whitespace(*str + i))
	{
		if (*(str + i) >= 'a' && *(str + i) <= 'z')
			return (0);
		str++;
	}
	return (1);
}

void	remove_whitespace(char **str)
{
	char	c;
	char	*h;

	h = *str;
	while (*(*str))
	{
		c = (*(*str));
		if (c == '\t' || c == '\n' || c == '\v' || c == '\r')
			*(*str) = ' ';
		(*str)++;
	}
	*str = h;
}

int	in_single_quotes(char *str, char *c)
{
	int	count;

	count = 0;
	while (*str && str < c)
	{
		if (*str == '\"')
		{
			str++;
			while (*str != '\"')
				str++;
		}
		if (*str == '\'')
			count++;
		str++;
	}
	return (count % 2 != 0);
}
