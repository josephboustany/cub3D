/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nassaf <nassaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 23:15:07 by nassaf            #+#    #+#             */
/*   Updated: 2025/12/13 03:12:55 by nassaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	**fill_array(char *cub_name)
{
	char	*str;
	int		lines;
	char	**array;
	int		i_str;
	int		i_arr;

	str = cub_to_str(cub_name);
	lines = count_lines(str);
	array = allocate_array(lines);
	i_str = 0;
	i_arr = 0;
	while (str[i_str])
	{
		array[i_arr] = get_line(str, i_str);
		while (str[i_str] && str[i_str] != '\n')
			i_str++;
		if (str[i_str] == '\n')
			i_str++;
		i_arr++;
	}
	array[i_arr] = NULL;
	free(str);
	return (array);
}

char	*skip_spaces(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	return (line + i);
}

int	line_is_empty(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

int	is_map(char c)
{
	if (c == '1' || c == '0' || c == ' ')
		return (1);
	return (0);
}

t_line_type	identify_line_type(char *line)
{
	char	*trimmed_line;

	trimmed_line = skip_spaces(line);
	if (ft_strncmp(trimmed_line, "NO ", 3) == 0)
		return (NORTH);
	if (ft_strncmp(trimmed_line, "SO ", 3) == 0)
		return (SOUTH);
	if (ft_strncmp(trimmed_line, "EA ", 3) == 0)
		return (EAST);
	if (ft_strncmp(trimmed_line, "WE ", 3) == 0)
		return (WEST);
	if (ft_strncmp(trimmed_line, "F ", 2) == 0)
		return (FLOOR);
	if (ft_strncmp(trimmed_line, "C ", 2) == 0)
		return (CEILING);
	if (line_is_empty(trimmed_line))
		return (EMPTY);
	if (is_map(trimmed_line[0]))
		return (MAP);
	return (ERROR);
}
