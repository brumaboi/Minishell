/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 16:44:48 by marvin            #+#    #+#             */
/*   Updated: 2024/10/11 16:44:48 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Create a new token and add it to the list
static t_token	*new_token(char *value, t_token_type type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = value;
	token->type = type;
	token->next = NULL;
	return (token);
}

// Add a token to the end of the list
static int	add_token_to_list(t_token **lst, t_token_type type, char *input, int *i)
{
	t_token	*new;
	t_token	*last;

	new = new_token(NULL, type);
	if (!new)
		return (1);
	if (*lst == NULL)
		*lst = new;
	else
	{
		last = *lst;
		while (last->next)
			last = last->next;
		last->next = new;
	}
	if (type == T_OPAR || type == T_CPAR || type == T_PIPE || type == T_GREAT || type == T_LESS)
		(*i)++;
	else if (type == T_DGREAT || type == T_DLESS || type == T_OR || type == T_AND)
		(*i) += 2;
	return (0);
}

static const char	*find_token_end(const char *start)
{
	int	in_single_quote;
	int	in_double_quote;

	in_single_quote = 0;
	in_double_quote = 0;
	while (*start && (in_single_quote || in_double_quote || (!ft_isspace(*start) && !is_special_char(start))))
	{
		if (quote_state_and_escape(start, &in_single_quote, &in_double_quote))
			start++;
		start++;
	}
	if (validate_quotes(in_single_quote, in_double_quote)) 
		return (NULL);
	return (start);
}

static int	count_delimiters(const char *str)
{
	int	spaces;
	int	in_single_quote;
	int	in_double_quote;

	spaces = 0;
	in_single_quote = 0;
	in_double_quote = 0;
    while (*str)
	{
		if (quote_state_and_escape(str, &in_single_quote, &in_double_quote))
			str++;
		else if (ft_isspace(*str) && !in_single_quote && !in_double_quote)
			spaces++;
		else if (is_special_char(str) && !in_single_quote && !in_double_quote)
			spaces++;
		str++;
	}
	return (spaces);
}

// Function to allocate and copy token content
static char	*copy_token(const char *start, const char *end)
{
	char	*result;
	int		in_single_quote = 0;
	int		in_double_quote = 0;
	int		i = 0;

	result = malloc((end - start + 1) * sizeof(char));
	if (!result)
		return (NULL);
	while (start < end)
	{
		if (quote_state_and_escape(start, &in_single_quote, &in_double_quote))
		{
			start++;
			result[i++] = *start;
		}
		else if ((*start != '\'' && *start != '"') || (in_single_quote || in_double_quote))
			result[i++] = *start;
		start++;
	}
	result[i] = '\0';
	return (result);
}

static char *process_special_char(const char *str)
{
    char *result;
    int len;

    len = special_char_len(str);
    result = malloc((len + 1) * sizeof(char));
    if (!result)
        return (NULL); /// should make a function to handle errors
    ft_strncpy(result, str, len);
    result[1] = '\0';
    return (result);
}

int is_special_char(const char *str)
{
    if (*str == '|' || *str == '<' || *str == '>' || *str == ';' || *str == '&' || *str == '(' || *str == ')') 
        return (1);
    if (ft_strncmp(str, ">>", 2) == 0 || ft_strncmp(str, "<<", 2) == 0
        || ft_strncmp(str, "&&", 2) == 0 || ft_strncmp(str, "||", 2) == 0)
        return (1);
    return (0);
}

int	special_char_len(const char *str)
{
	if (str[0] == '|' || str[0] == '<' || str[0] == '>' || str[0] == '&')
	{
		if (str[0] == str[1])
			return (2);
		return (1);
	}
	return (0);
}

// Handles quote toggling and escape sequences
static int	quote_state_and_escape(const char *str, int *in_single_quote, int *in_double_quote)
{
	if (*str == '\\' && *(str + 1) && !*in_single_quote)
		return (1);
	if (*str == '"' && !*in_single_quote)
		*in_double_quote = !*in_double_quote;
	else if (*str == '\'' && !*in_double_quote)
		*in_single_quote = !*in_single_quote;
	return (0);
}

// Function to validate unmatched quotes
static int	validate_quotes(int in_single_quote, int in_double_quote)
{
	if (in_single_quote || in_double_quote)
	{
		write(2, "syntax error: unmatched quote\n", 30);
		return (1);
	}
	return (0);
}

int token_add(char *inpu, int i, t_token **lst)
{
    if (input[*i] == '>' && input[*i + 1] == '>')
		return (add_token_to_list(lst, T_DGREAT, input, i));
	else if (input[*i] == '>')
		return (add_token_to_list(lst, T_GREAT, input, i));
	else if (input[*i] == '<' && input[*i + 1] == '<')
		return (add_token_to_list(lst, T_DLESS, input, i));
	else if (input[*i] == '<')
		return (add_token_to_list(lst, T_LESS, input, i));
	else if (input[*i] == '|' && input[*i + 1] == '|')
		return (add_token_to_list(lst, T_OR, input, i));
	else if (input[*i] == '|')
		return (add_token_to_list(lst, T_PIPE, input, i));
	else if (input[*i] == '&' && input[*i + 1] == '&')
		return (add_token_to_list(lst, T_AND, input, i));
    else if (input[*i] == '&')
        return (add_token_to_list(lst, T_BACKGROUND, input, i));
	else if (input[*i] == '(')
		return (add_token_to_list(lst, T_OPAR, input, i));
	else if (input[*i] == ')')
		return (add_token_to_list(lst, T_CPAR, input, i));
    else if (input[*i] == ';')
        return (add_token_to_list(lst, T_SEMICOLON, input, i));
	else
		return (add_token_to_list(lst, T_IDENTIFIER, input, i));
}

char **split_input(const char *str, int *count, t_token **lst)
{
    int spaces;
    char **result;
    int idx;
    const char *end;

    idx = 0;
    spaces = count_delimiters(str);
    result = malloc((spaces + 2) * sizeof(char *));
    if (!result)
        return (NULL); /// should make a function to handle errors
    while (*str)
    {
        while (ft_isspace(*str))
            str++;
        if (is_special_char(str))
        {
            result[idx++] = process_special_char(str);
            str += special_char_len(str);
        }
        else if (*str)
        {
            end = find_token_end(str);
            if(!end)
                return (NULL); /// should make a function to handle errors
            result[idx++] = copy_token(str, end);
            token_add((char *)str, (int *)&idx, lst);
            str = end;
        }
    }
    result[idx] = NULL;
    *count = idx;
    return (result);
}
