/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acerrah <alierdemcerrah@student.42.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 22:12:58 by acerrah           #+#    #+#             */
/*   Updated: 2023/10/10 22:13:01 by acerrah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

extern t_data *g_data;

/*  Lexer divides the input string into tokens and stores them in a dynamic   */
/*  array. The tokens are separated by pipes with attention to quotes.        */
/*  The tokens are stored in the dynamic array in the following order:        */
/*  <token, pipe, token, pipe, token, pipe, token, NULL>                      */
void lexer(char *input_str, bool in_single_quotes,
    bool in_double_quotes, int last_pipe, int i)
{
    while (input_str[i])
    {
        if (input_str[i] == '|' && !in_single_quotes && !in_double_quotes)
        {
            dynarray_push(g_data->lex,
                ft_substr(input_str, last_pipe, i - last_pipe));
            dynarray_push(g_data->lex, ft_substr(input_str, i, 1));
            last_pipe = i + 1;
        }
        else if (input_str[i] == '\'' && !in_double_quotes) 
            in_single_quotes = !in_single_quotes;
        else if (input_str[i] == '"' && !in_single_quotes)
            in_double_quotes = !in_double_quotes;
        else if (input_str[i + 1] == '\0')
        {
            dynarray_push(g_data->lex,
                ft_substr(input_str, last_pipe, i + 1 - last_pipe));
            dynarray_push(g_data->lex, NULL);
        }
        i++;
    }
}