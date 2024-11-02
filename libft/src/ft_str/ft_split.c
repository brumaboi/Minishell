/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 11:22:42 by sbruma            #+#    #+#             */
/*   Updated: 2024/11/02 11:35:19 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

int count_words(const char *s, char c)
{
    int i = 0;
    int count = 0;
    int in_word = 0;

    if (!s)
        return 0;  // Handle NULL input

    while (s[i])
    {
        if (s[i] != c && !in_word)
        {
            in_word = 1;
            count++;
        }
        else if (s[i] == c)
        {
            in_word = 0;
        }
        i++;
    }
    return count;
}

char *allocate_word(const char *s, int word_len)
{
    char *word = malloc((word_len + 1) * sizeof(char));
    int i = 0;

    if (!word)
        return NULL;
    while (i < word_len)
    {
        word[i] = s[i];
        i++;
    }
    word[i] = '\0';
    return word;
}

void free_all(char **result, int j)
{
    while (--j >= 0)
        free(result[j]);
    free(result);
}

char **fill_result(const char *s, char c, char **result)
{
    int i = 0, j = 0;

    while (s[i])
    {
        if (s[i] != c)
        {
            int word_len = 0;
            while (s[i + word_len] && s[i + word_len] != c)
                word_len++;
            result[j] = allocate_word(&s[i], word_len);
            if (!result[j])
            {
                free_all(result, j);  // Free previously allocated memory on failure
                return NULL;
            }
            j++;
            i += word_len;
        }
        else
            i++;
    }
    result[j] = NULL;
    return result;
}

char **ft_split(const char *s, char c)
{
    if (!s)
        return NULL;  // Handle NULL input

    int num_words = count_words(s, c);
    char **result = malloc((num_words + 1) * sizeof(char *));
    
    if (!result)
        return NULL;
    return fill_result(s, c, result);
}
