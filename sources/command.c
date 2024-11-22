/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarumuga <jarumuga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 22:42:54 by habernar          #+#    #+#             */
/*   Updated: 2024/10/15 22:11:29 by jarumuga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_directory(t_shell *shell, t_cmd *cmd)
{
	struct stat	pathstat;

	if (!stat(cmd->params[0], &pathstat))
	{
		if (S_ISDIR(pathstat.st_mode))
		{
			printf("minishell : %s : is a directory\n", cmd->params[0]);
			cmd->error = 1;
			shell->exit_code = 126;
			return (true);
		}
	}
	return (false);
}

static char	**make_params(char *str)
{
	char	**ret;
	char	quotes;
	char	*head;

	quotes = 0;
	head = str;
	while (*str)
	{
		if (*str == '\'' || *str == '\"')
		{
			quotes = *str++;
			while (*str && *str != quotes)
			{
				if (*str == ASCII_SPACE)
					*str = 31;
				str++;
			}
			if (*str == quotes)
				quotes = 0;
		}
		str++;
	}
	ret = ft_split(head, ASCII_SPACE);
	return (ret);
}

static char	*make_path(t_shell *shell, char *cmdname)
{
	char	**paths;
	char	*path;
	t_item	*item;
	int		idx;

	if (access(cmdname, X_OK) == 0)
		return (ft_strdup(cmdname));
	item = hashtable_search(shell->ht, "PATH");
	if (!item)
		return (0);
	paths = ft_split(item->value, ':');
	idx = 0;
	while (paths && paths[idx])
	{
		path = ft_strjoin_slash(paths[idx], cmdname, '/');
		if (access(path, F_OK) == 0)
			return (free_tab(paths), path);
		free(path);
		idx++;
	}
	return (free_tab(paths), (char *)0);
}

static t_cmd	*init_command(void)
{
	t_cmd	*c;

	c = (t_cmd *)malloc(sizeof(t_cmd));
	if (!c)
	{
		perror("malloc");
		return (0);
	}
	c->error = 0;
	c->path = 0;
	c->params = 0;
	c->lstfiles = 0;
	return (c);
}

void	make_command(t_shell *shell, t_astnode *n)
{
	n->cmd = init_command();
	if (!n->cmd)
		return (n->cmd->error = 1, (void)0);
	n->ps = expand_env_variables(shell, n->ps);
	get_redirs(shell, n->cmd, n->ps);
	remove_redirs(n->ps);
	remove_whitespace(&n->ps);
	if (!*n->ps || nothing_to_parse(n->ps))
		return (n->cmd->error = 1, (void)0);
	n->cmd->params = make_params(n->ps);
	if (!n->cmd->params || !*n->cmd->params || is_directory(shell, n->cmd))
		return (n->cmd->error = 1, (void)0);
	expand_quotes(n->cmd->params);
	expand_wildcard(n->cmd);
	remove_quotes(n->cmd->params);
	n->cmd->path = make_path(shell, n->cmd->params[0]);
	if ((!n->cmd->path || n->cmd->params[0][0] == 0) \
	&& !is_builtin(n->cmd->params[0]))
	{
		if (ft_strchr(n->cmd->params[0], '/'))
			printf(MSG_ERROR_FILEORDIR, n->cmd->params[0]);
		else
			printf("minishell : %s : command not found\n", n->cmd->params[0]);
		return (n->cmd->error = 1, shell->exit_code = 127, (void)0);
	}
}
