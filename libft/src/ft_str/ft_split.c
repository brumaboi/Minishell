/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 11:22:42 by sbruma            #+#    #+#             */
/*   Updated: 2024/12/11 01:54:43 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

int	count_words(const char *s, char c)
{
	int	i;
	int	count;
	int	in_word;

	i = 0;
	count = 0;
	in_word = 0;
	if (!s)
		return (0);
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
	return (count);
}

char	*allocate_word(const char *s, int word_len)
{
	char	*word;
	int		i;

	i = 0;
	word = malloc((word_len + 1) * sizeof(char));
	if (!word)
		return (NULL);
	while (i < word_len)
	{
		word[i] = s[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

void	free_all(char **result, int j)
{
	while (--j >= 0)
		free(result[j]);
	free(result);
}

char	**fill_result(const char *s, char c, char **result)
{
	int	i;
	int	j;
	int	word_len;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			word_len = 0;
			while (s[i + word_len] && s[i + word_len] != c)
				word_len++;
			result[j] = allocate_word(&s[i], word_len);
			if (!result[j])
				return (free_all(result, j), NULL);
			j++;
			i += word_len;
		}
		else
			i++;
	}
	result[j] = NULL;
	return (result);
}

char	**ft_split(const char *s, char c)
{
	int		num_words;
	char	**result;

	if (!s)
		return (NULL);
	num_words = count_words(s, c);
	*result = malloc((num_words + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	return (fill_result(s, c, result));
}
