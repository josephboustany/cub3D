/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nassaf <nassaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 01:09:18 by nassaf            #+#    #+#             */
/*   Updated: 2026/02/09 23:03:28 by nassaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_map	*allocate_map_struct(char **array)
{
	t_map	*pointer_to_return;

	pointer_to_return = malloc(sizeof(t_map));
	if (!pointer_to_return)
	{
		free_array(array);
		error_exit("Failed to malloc t_map in allocate_map_struct() function");
	}
	pointer_to_return->grid = NULL;
	pointer_to_return->width = 0;
	pointer_to_return->height = 0;
	pointer_to_return->north_texture = NULL;
	pointer_to_return->south_texture = NULL;
	pointer_to_return->east_texture = NULL;
	pointer_to_return->west_texture = NULL;
	pointer_to_return->floor_color = -1;
	pointer_to_return->ceiling_color = -1;
	return (pointer_to_return);
}

int	skip_spaces_descript(char *array)
{
	int	i;

	i = 0;
	while (array[i] == ' ' || array[i] == '\t')
		i++;
	while (array[i] && array[i] != ' ' && array[i] != '\t')
		i++;
	while (array[i] == ' ' || array[i] == '\t')
		i++;
	return (i);
}

char	*extract_path_from_line(char *array, t_map *map_data)
{
	int		i;
	int		start;
	int		len;
	char	*to_return;

	start = skip_spaces_descript(array);
	i = start;
	while (array[i] && array[i] != ' ' && array[i] != '\t' && array[i] != '\n')
		i++;
	len = i - start;
	to_return = malloc(sizeof(char) * (len + 1));
	if (!to_return)
	{
		free_map_data(map_data);
		error_exit("Failed to malloc in extract_data_from_lines");
	}
	i = -1;
	while (++i < len)
		to_return[i] = array[start + i];
	to_return[i] = '\0';
	return (to_return);
}

void	assign_texture(char **texture,
				char *line, t_map *map_data, char *err)
{
	if (*texture)
	{
		free_map_data(map_data);
		error_exit(err);
	}
	*texture = extract_path_from_line(line, map_data);
}

void	handle_texture_line(t_line_type type,
				char *line, t_map *map_data)
{
	if (type == NORTH)
		assign_texture(&map_data->north_texture,
			line, map_data, "Duplicate NORTH texture");
	else if (type == SOUTH)
		assign_texture(&map_data->south_texture,
			line, map_data, "Duplicate SOUTH texture");
	else if (type == EAST)
		assign_texture(&map_data->east_texture,
			line, map_data, "Duplicate EAST texture");
	else if (type == WEST)
		assign_texture(&map_data->west_texture,
			line, map_data, "Duplicate WEST texture");
}
