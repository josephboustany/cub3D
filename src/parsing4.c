/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nassaf <nassaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 00:02:23 by nassaf            #+#    #+#             */
/*   Updated: 2026/02/09 23:34:16 by nassaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	get_paths(char **array, t_map *map_data)
{
	int			i;
	t_line_type	line_type;

	i = 0;
	while (array[i])
	{
		line_type = identify_line_type(array[i]);
		if (line_type == MAP)
			break ;
		handle_texture_line(line_type, array[i], map_data);
		i++;
	}
}

int	parse_rgb_value(char *s, int *i)
{
	int	value;
	int	digits;

	value = 0;
	digits = 0;
	while (s[*i] == ' ' || s[*i] == '\t')
		(*i)++;
	while (s[*i] >= '0' && s[*i] <= '9')
	{
		value = value * 10 + (s[*i] - '0');
		(*i)++;
		digits++;
	}
	if (digits == 0 || value > 255)
		return (-1);
	return (value);
}

int	create_rgb(char *array, t_map *map_data)
{
	int	r;
	int	g;
	int	b;
	int	i;

	i = skip_spaces_descript(array);
	r = parse_rgb_value(array, &i);
	if (r < 0 || array[i] != ',')
		free_and_exit(map_data, "Invalid RGB format");
	i++;
	g = parse_rgb_value(array, &i);
	if (g < 0 || array[i] != ',')
		free_and_exit(map_data, "Invalid RGB format");
	i++;
	b = parse_rgb_value(array, &i);
	if (b < 0)
		free_and_exit(map_data, "Invalid RGB format");
	while (array[i] == ' ' || array[i] == '\t')
		i++;
	if (array[i] && array[i] != '\n')
		free_and_exit(map_data, "Invalid RGB format");
	return ((r << 16) | (g << 8) | b);
}

void	get_color(char **array, t_map *map_data)
{
	int			i;
	t_line_type	line_type;

	i = 0;
	line_type = identify_line_type(array[i]);
	while (line_type != MAP)
	{
		if (line_type == FLOOR)
		{
			if (map_data->floor_color != -1)
				free_and_exit(map_data, "Duplicate Floor Color");
			map_data->floor_color = create_rgb(array[i], map_data);
		}
		if (line_type == CEILING)
		{
			if (map_data->ceiling_color != -1)
				free_and_exit(map_data, "Duplicate Ceiling Color");
			map_data->ceiling_color = create_rgb(array[i], map_data);
		}
		i++;
		if (!array[i])
			break ;
		line_type = identify_line_type(array[i]);
	}
}

int	find_map_index(char **array)
{
	int			i;
	t_line_type	type;

	i = 0;
	if (!array || !array[i])
		return (-1);
	type = identify_line_type(array[i]);
	while (array[i] && type != MAP)
	{
		i++;
		if (!array[i])
			break ;
		type = identify_line_type(array[i]);
	}
	if (type == MAP)
		return (i);
	return (-1);
}
