#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


t_data *custom_env;


int main(int argc, char *argv[]) {
    if (argc != 2)
	{
        printf("Usage: export VARIABLE_NAME=VALUE\n");
        return 1;
    }

    char *env_var = argv[1];

    // Find the position of the equal sign '='
    char *equal_sign = strchr(env_var, '=');

    if (!equal_sign) {
        printf("Invalid format. Use VARIABLE_NAME=VALUE\n");
        return 1;
    }

    // Split the variable name and value
    *equal_sign = '\0';
    char *var_name = env_var;
    char *var_value = equal_sign + 1;

	// Allocate memory for the custom_env structure
   custom_env = (t_data *)malloc(sizeof(t_data));
    if (custom_env == NULL) {
        perror("malloc");
        return 1;
    }


    // Search for the variable in the custom environment
    int var_index = -1;
    int i = 0;
    while (i < MAX_ENV_VARS) {
        if (custom_env->export[i] != NULL && strncmp(custom_env->export[i], var_name, equal_sign - var_name) == 0 && custom_env->export[i][equal_sign - var_name] == '=') {
            var_index = i;
            break;
        }
        i++;
    }

    // If the variable exists, update its value
    if (var_index != -1) {
        free(custom_env->export[var_index]); // Free the old value
        custom_env->export[var_index] = (char *)malloc(strlen(var_name) + strlen(var_value) + 2); // +2 for '=' and '\0'
        if (custom_env->export[var_index] == NULL) {
            perror("malloc");
            free_custom_env(custom_env);
            return 1;
        }
    } else {
        // Find an empty slot in the custom environment
        int empty_index = -1;
        i = 0;
        while (i < MAX_ENV_VARS) {
            if (custom_env->export[i] == NULL) {
                empty_index = i;
                break;
            }
            i++;
        }

        if (empty_index == -1) {
            fprintf(stderr, "Error: Custom environment is full.\n");
            free_custom_env(custom_env);
            return 1;
        }

        custom_env->export[empty_index] = (char *)malloc(strlen(var_name) + strlen(var_value) + 2);
        if (custom_env->export[empty_index] == NULL) {
            perror("malloc");
            free_custom_env(custom_env);
            return 1;
        }
    }

    // Print the updated custom environment
    i = 0;
    while (i < MAX_ENV_VARS) {
        if (custom_env->export[i] != NULL) {
            printf("%s\n", custom_env->export[i]);
        }
        i++;
    }

    // Clean up allocated memory
    free_custom_env(custom_env);

    return 0;
}
