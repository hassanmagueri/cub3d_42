/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 00:21:05 by belguabd          #+#    #+#             */
/*   Updated: 2024/08/13 12:40:14 by belguabd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

typedef struct s_splt
{
	char	**res;
	int		i;
	int		j;
	int		to_find;
}	t_splt;

static int	count_words(const char *str, char c)
{
	int	i;
	int	to_find;

	i = 0;
	to_find = 0;
	while (*str)
	{
		if (*str != c && to_find == 0)
		{
			to_find = 1;
			i++;
		}
		else if (*str == c)
			to_find = 0;
		str++;
	}
	return (i);
}

static char	*word_dup(const char *str, int start, int end)
{
	char	*word;
	int		i;

	word = (char *)ft_malloc(((end - start) + 1) * sizeof(char), ALLOC);
	if (!word)
		return (NULL);
	i = 0;
	while (start < end)
		word[i++] = str[start++];
	word[i] = '\0';
	return (word);
}

static void	process_character(t_splt *spl, const char *s, char c)
{
	if (s[spl->i] != c && spl->to_find < 0)
		spl->to_find = spl->i;
	else if ((s[spl->i] == c || spl->i == (int)ft_strlen(s)) 
		&& spl->to_find >= 0)
	{
		spl->res[spl->j++] = word_dup(s, spl->to_find, spl->i);
		if (!spl->res[spl->j - 1])
		{
			while (spl->j-- - 1)
			{
				free(spl->res[spl->j - 1]);
			}
			free(spl->res);
			spl->res = NULL;
			return ;
		}
		spl->to_find = -1;
	}
}

char	**ft_split(char const *s, char c)
{
	t_splt	spl;

	if (!s)
		return (NULL);
	spl.res = (char **)ft_malloc((count_words(s, c) + 1) * sizeof(char *), ALLOC);
	if (!spl.res)
		return (NULL);
	spl.i = -1;
	spl.j = 0;
	spl.to_find = -1;
	while (++spl.i <= (int)ft_strlen(s))
	{
		process_character(&spl, s, c);
		if (spl.res == NULL)
			return (NULL);
	}
	spl.res[spl.j] = 0;
	return (spl.res);
}
