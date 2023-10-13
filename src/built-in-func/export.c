/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iremoztimur <iremoztimur@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 22:11:47 by iremoztimur       #+#    #+#             */
/*   Updated: 2023/10/13 18:49:20 by iremoztimur      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

extern t_data *g_data;

int	int_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	if (!s && *s != 0)
		return (0);
	while (s[i] != 0)
	{
		if (s[i] == (char)c)
			return (1);
		i++;
	}
	return (0);
}

char	*add_quotes(char *str)
{
	int i;
	int len;
	char *new_str;
	int j;

	i = 1;
	j = 0;
	len = ft_strlen(str);
	new_str = (char *)malloc(sizeof(char) * len + 3);
	new_str[0] = '\"';
	while(str[j])
	{
		new_str[i] = str[j];
		i++;
		j++;
	}
	new_str[len + 1] = '\"';
	new_str[len + 2] = '\0';
	free(str);
	return(new_str);
}


int len_env(char **environment)
{
	int i;

	i = 0;
	while (environment[i])
		i++;
	return (i);
}

void write_exp(void)
{
	int i;

	i = 0;
	while (g_data->exp->data[i])
	{
		printf("declare -x %s\n", g_data->exp->data[i]);
		i++;
	}
}

char *format_exp(char *command)
{
	char *variable;
	char *value;
	char **str;
	char *ret;

	str = ft_split(command, '=');
	variable = ft_strdup(str[0]);
	if (str[1])
	{
		if (str[1][0] != '\"' && str[1][ft_strlen(str[1] - 1)] != '\"')
			value = add_quotes(ft_strdup(str[1]));
		else
			value = ft_strdup(str[1]);
	}
	else
		value = ft_strdup("");
	ret = ft_strjoin(ft_strjoin(variable, "="), value);
	free(variable);
	free(value);
	return (ret);
}

int syntax_check(char *command)
{
	char *variable;
	if (ft_strchr(command, '=') != 0)
	{
		variable = ft_split(command, '=')[0];
		return (int_strchr(variable, 32));
	}
	else
		return (0);
}

void single_to_double_quote(char *command)
{
	if (command[0] == '\'' && command[ft_strlen(command) - 1] == '\'')
	{
		command[0] = '\"';
		command[ft_strlen(command) - 1] = '\"';
		return ;
	}
}

// Here is to remove double quotes from the command
/*
char *format_env(char *command)
{
	char **raw_str;
	char *res;
	int len;
	int i;

	i = 0;
	res = "a";
	if (ft_strchr(command, '\"') != 0)
	{
		raw_str = ft_split(command, '\"');
		len = len_env(raw_str);
		while (i < len)
		{
			ft_strjoin(res, raw_str[i]);
			i++;
		}
	}
	else
		res = ft_strdup(command);
	return (res);
}
*/

void ft_export(char **command)
{
	int i;

	i = 1;
	if (command[i] == 0)
		write_exp();
	else
	{
		while (command[i])
		{
			single_to_double_quote(command[i]);
			// Here is for syntax check like having digits or '=' before variable name causes an error
			if (command[i][0] == '=' || ft_isdigit(command[i][0]) ||
			syntax_check(command[i]))
			{
				printf("bash: export: '%s': not a valid identifier\n", command[i]);
				i++;
				continue ;
			}
			else if (command[i][0] != '=')
			{
				if (command[i][ft_strlen(command[i]) - 1] == '=')
					dynarray_push(g_data->exp, ft_strjoin("declare -x ", ft_strjoin(command[i], "\"\"")));
				else
					dynarray_push(g_data->exp, ft_strjoin("declare -x ", format_exp(command[i])));
			}
			// if variable has a value add to env
			if (int_strchr(command[i], '='))
				dynarray_push(g_data->env, command[i]);
			i++;
		}
	}
}
