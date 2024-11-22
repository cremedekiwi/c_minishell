/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variable.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habernar <habernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 22:45:47 by habernar          #+#    #+#             */
/*   Updated: 2024/10/15 20:09:58 by habernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*expand_digit(t_shell *shell, char *str, char *dsign)
{
	char	*s;
	char	*nb_string;
	int		i;
	int		nb;

	i = 1;
	nb = 0;
	while (*(dsign + i) && (ft_isdigit(*(dsign + i))))
	{
		nb = nb * 10 + *(dsign + i) - '0';
		i++;
	}
	if (nb > shell->argc || (!shell->argv || !shell->argv[nb]))
		return (erase_digit(str, dsign));
	nb_string = shell->argv[nb];
	s = (char *)malloc((ft_strlen(str) - i + ft_strlen(nb_string) + 1));
	if (!s)
		return (0);
	*s = 0;
	ft_strlcat(s, str, dsign - str + 1);
	ft_strlcat(s, nb_string, ft_strlen(s) + ft_strlen(nb_string) + 1);
	ft_strlcat(s, dsign + i, ft_strlen(s) + ft_strlen(dsign + i) + 1);
	return (s);
}

static char	*expand_alpha(t_shell *shell, char *str, char *dsign)
{
	char	*s;
	char	*key;
	int		i;
	t_item	*item;

	i = 1;
	while (*(dsign + i) && (ft_isalnum(*(dsign + i)) || *(dsign + i) == '_'))
		i++;
	key = ft_strndup(dsign + 1, i - 1);
	if (!key)
		return (0);
	item = hashtable_search(shell->ht, key);
	free(key);
	if (!item || !item->value)
		return (erase_alpha(str, dsign));
	s = (char *)malloc((ft_strlen(str) - i + ft_strlen(item->value) + 1));
	if (!s)
		return (0);
	*s = 0;
	ft_strlcat(s, str, dsign - str + 1);
	ft_strlcat(s, item->value, ft_strlen(s) + ft_strlen(item->value) + 1);
	ft_strlcat(s, dsign + i, ft_strlen(s) + ft_strlen(dsign + i) + 1);
	return (s);
}

static char	*expand_exit_value(t_shell *shell, char *str, char *dsign)
{
	char	*s;
	char	*tmp;
	int		size;

	tmp = ft_itoa(shell->exit_code);
	size = ft_strlen(str) - 2 + ft_strlen(tmp) + 1;
	s = (char *)malloc(sizeof(char) * size);
	if (!s)
	{
		perror("malloc");
		return (0);
	}
	*s = 0;
	ft_strlcat(s, str, dsign - str + 1);
	ft_strlcat(s, tmp, size);
	ft_strlcat(s, dsign + 2, size);
	free(tmp);
	return (s);
}

static char	*expanded_string(t_shell *shell, char *str, char *dsign)
{
	if (*(dsign + 1) && *(dsign + 1) == '?')
		return (expand_exit_value(shell, str, dsign));
	else if (*(dsign + 1) && ft_isdigit(*(dsign + 1)))
		return (expand_digit(shell, str, dsign));
	else if (*(dsign + 1) && (ft_isalpha(*(dsign + 1)) || *(dsign + 1) == '_'))
		return (expand_alpha(shell, str, dsign));
	else
		return (0);
}

char	*expand_env_variables(t_shell *shell, char *str)
{
	char	*new;
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && !in_single_quotes(str, str + i))
		{
			new = expanded_string(shell, str, str + i);
			if (new)
			{
				free(str);
				return (expand_env_variables(shell, new));
			}
		}
		i++;
	}
	return (str);
}
