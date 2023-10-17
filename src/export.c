/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acerrah <alierdemcerrah@student.42.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 22:11:47 by iremoztimur       #+#    #+#             */
/*   Updated: 2023/10/10 23:09:55 by acerrah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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

char *format_str(char *command)
{
	char *variable;
	char *value;
	char **str;
	char *ret;

	str = ft_split(command, '=');
	variable = ft_strdup(str[0]);
	if (str[1])
		value = add_quotes(ft_strdup(str[1]));
	else
		value = ft_strdup("");
	ret = ft_strjoin(ft_strjoin(variable, "="), value);
	free(command);
	free(variable);
	free(value);
	return (ret);
}

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
			// Here is for syntax check like having digits or '=' before variable name causes an error
			if (command[i][0] == '=' || ft_isdigit(command[i][0]) ||
			int_strchr(command[i], 32))
			{
				printf("bash: export: '%s': not a valid identifier", command[i]);
				i++;
				continue ;
			}
			else
				dynarray_push(g_data->exp, ft_strjoin("declare -x ", command[i]));
			if (int_strchr(command[i], '='))
				dynarray_push(g_data->env, format_str(command[i]));
			i++;
		}
	}
}
