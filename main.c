#include "minishell.h"

t_data *global_var;

static void write_env(void)
{
	int i;

	i = 0;
	while (global_var->env[i])
		printf("declare -x %s\n", global_var->env[i++]);
}


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

static char *rewrite_env(char *command, int i)
{
    char *variable;
    char *value;
    char *ret;

    // Check if the command contains an '=' character
    if (int_strchr(command, '='))
    {
        while (command[i] != '=')
            i++;

        // Extract the part before '=' and the part after '='
        variable = ft_substr(command, 0, i + 1);
        value = ft_substr(command, i + 1, ft_strlen(command) - (i + 1));

        // Add a double quote character '"' to the beginning of 'two'
        value = add_quotes(value);

        // Concatenate 'first' and 'two' to create the updated string
        ret = ft_strjoin(variable, value);

        // Free the memory used by 'first' and 'two'
        free(variable);
        free(value);
    }
    else
    {
        // If there is no '=', duplicate the original command
        ret = ft_strdup(command);
    }
    return (ret);
}

char	*duplicate_command(char *command)
{
	char	*new;

	new = rewrite_env(command, 0);
	return (new);
}


static char	*update_env(char *previous_var, char *command)
{
	int		len;
	char	*new;

	// Calculate the length of the new variable
	if (int_strchr(command, '='))
		len = ft_strlen(command) + 3;
	else
		len = ft_strlen(command) + 1;

	// Allocate memory for the new variable
	new = ft_calloc(sizeof(char), len);

	new = rewrite_env(command, 0);

	free(previous_var);
	return (new);
}
int len_env(char **environment)
{
	int i;

	i = 0;
	while (environment[i])
		i++;
	return (i);
}
void free_prev_env(char **env)
{
	int i;

	i = 0;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
}

static char	**add_variable_to_env(char **environment, char *new_var)
{
	char	**ret;
	int		i;

	i = 0;

	// Allocate memory for the new environment with an extra slot
	ret = ft_calloc(sizeof(char *), len_env(environment) + 2);
	// Copy existing environment variables to the new environment
	while (environment[i] != 0)
	{
		ret[i] = ft_strdup(environment[i]);
		i++;
	}
	ret[i] = new_var;
	free_prev_env(environment);
	return (ret);
}

static void add_environment(char *command)
{
	int i;
	int j;
	int flag;
	char *new_variable;

	i = -1;
	j = 0;
	flag = 0;
	// Find the position of the equal sign '='
	while (command[j] && command[j] != '-')
		j++;

	// Search for the variable in the custom environment
	while (global_var->env[++i])
	{
		flag = ft_strncmp(global_var->env[i], command, j);
		if (flag == 0)
			break;
	}
	// If the variable exists, update its value
	if (flag == 0)
		global_var->env[i] = update_env(global_var->env[i], command);
	// If doesn't exist, create new variable and add it to the custom environment
	else
	{
		new_variable = duplicate_command(command);
		global_var->env = add_variable_to_env(global_var->env, new_variable);
	}
}

void ft_export(char **command)
{
	int i;

	i = 1;
	if (command[i] == 0)
		write_env();
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
				add_environment(command[i]);
			//if (int_strchr(command[i], '='))
				//add_env(command[i]);
			i++;
		}
	}
}

int main(int argc, char **av, char **env)
{
    if (!argc || !av || !env)
        return (0);
    //copy env into global_var->env
    global_var = (t_data *)malloc(sizeof(t_data));
    global_var->env = ft_calloc(sizeof(char *), len_env(env) + 1);
    int i = 0;
    while (env[i])
    {
        global_var->env[i] = ft_strdup(env[i]);
        i++;
    }

    ft_export(av);

    for (int i = 0; global_var->env[i]; i++)
        printf("%s\n", global_var->env[i]);

    return (0);
}
