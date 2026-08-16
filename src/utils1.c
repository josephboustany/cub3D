/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nassaf <nassaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 22:35:55 by nassaf            #+#    #+#             */
/*   Updated: 2026/02/22 20:04:10 by nassaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

int	ft_strncmp(char *str1, char *str2, int n)
{
	int	i;

	if (!str1 || !str2)
		return (1);
	i = 0;
	while (i < n && str1[i] && str2[i])
	{
		if (str1[i] != str2[i])
			return (1);
		i++;
	}
	if (i == n)
		return (0);
	return (1);
}

int	ft_atoi(const char *nptr)
{
	int		i;
	int		sign;
	int		num;
	char	*str;

	i = 0;
	sign = 1;
	num = 0;
	str = (char *)nptr;
	while (str[i] == 9 || str[i] == 10 || str[i] == 11
		|| str[i] == 12 || str[i] == 13 || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + (str[i] - '0');
		i++;
	}
	return (num * sign);
}

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free (array[i]);
		i++;
	}
	free(array);
}

void	error_exit(char *message)
{
	int	i;

	i = 0;
	write (2, "Error\n", 6);
	if (message)
	{
		while (message[i])
		{
			write (2, &message[i], 1);
			i++;
		}
		write (2, "\n", 1);
	}
	exit (1);
}
