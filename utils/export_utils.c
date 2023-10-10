#include "minishell.h"

t_data	*g_data;

//Function to extract part of the 'command' string until the '=' character and add double quotes
static char	*in_array(char *command, int i)
{
	char	*first;
	char	*two;
	char	*ret;

	if (int_strchr(command, '='))
	{
		while (command[i] != '=')
			i++;
		first = ft_substr(command, 0, i + 1);
		two = ft_substr(command, i + 1, ft_strlen(command) - (i + 1));
		two = add_char(two, '\"');
		ret = ft_strjoin(first, two);
		free(first);
		free(two);
	}
	else
		ret = ft_strdup(command);
	return (ret);
}

char	*new_strdup(char *command)
{
	char	*new;

	new = in_array(command, 0);
	return (new);
}

char	*free_new_strdup(char *_free, char *command, int flag)
{
	int		len;
	char	*new;

	if (int_strchr(command, '='))
		len = ft_strlen(command) + 3;
	else
		len = ft_strlen(command) + 1;
	new = ft_calloc(sizeof(char), len);
	if (flag == 1)
		new = in_array(command, 0);
	else if (flag == 0)
		new = ft_strdup(command);
	free(_free);
	return (new);
}

char	**double_strjoin(char **s1, char *add)
{
	char	**ret;
	int		i;

	i = 0;
	ret = ft_calloc(sizeof(char *), chardb_len(s1) + 2);
	while (s1[i] != 0)
	{
		ret[i] = ft_strdup(s1[i]);
		i++;
	}
	ret[i] = add;
	free_command_db(s1);
	return (ret);
}
