/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsoltys <vsoltys@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 12:33:05 by vsoltys           #+#    #+#             */
/*   Updated: 2024/07/22 15:22:09 by vsoltys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"

static int	countoccur(char const *s, int i, char c)
{
	int	num;

	num = 0;
	while (s[i] && s[i] != c)
	{
		num++;
		i++;
	}
	return (num);
}

static int	compteurmots(char const *s, char c)
{
	int	i;
	int	num;

	i = 0;
	num = 0;
	if (s[i] == '\0')
		return (0);
	while (s[i + 1])
	{
		if (s[i] == c && s[i + 1] != c)
			num++;
		i++;
	}
	if (s[0] != c)
		num++;
	return (num);
}

static char	**souspartie(const char *s, char **str, char c)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] && s[i] == c)
			i++;
		else
		{
			str[j] = (char *)malloc(sizeof(char) * (countoccur(s, i, c) + 1));
			k = 0;
			while (s[i] && s[i] != c)
			{
				str[j][k] = s[i];
				i++;
				k++;
			}
			str[j][k] = '\0';
			j++;
		}
	}
	return (str);
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	int		n;

	if (!s)
		return (NULL);
	n = compteurmots(s, c);
	str = (char **)malloc(sizeof(char *) * (n + 1));
	if (str == NULL)
		return (NULL);
	str[n] = NULL;
	return (souspartie(s, str, c));
}
/*int main(void)
{
    const char *s = "hello,world,this,is";
    char c = ',';
    char **result = ft_split(s, c);
    
    int i = 0;
    while (result[i] != NULL)
    {
        printf("%s\n", result[i]);
        free(result[i]);
        i++;
    }

    free(result);
    return (0);
}*/
