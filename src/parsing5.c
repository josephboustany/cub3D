/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing5.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nassaf <nassaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 00:05:59 by nassaf            #+#    #+#             */
/*   Updated: 2026/02/09 22:10:49 by nassaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	get_width(char **array, t_map *map_data)
{
	int	i;
	int	length;
	int	max_length;

	i = find_map_index(array);
	if (i == -1)
	{
		free_array(array);
		free_and_exit(map_data, "No map found in the .cub file");
	}
	length = 0;
	max_length = 0;
	while (array[i])
	{
		length = ft_strlen(array[i]);
		if (length > max_length)
			max_length = length;
		i++;
	}
	map_data->width = max_length;
}

void	get_height(char **array, t_map *map_data)
{
	int	i;
	int	height;

	i = find_map_index(array);
	if (i == -1)
	{
		free_array(array);
		free_and_exit(map_data, "No map found in the .cub file");
	}	
	height = 0;
	while (array[i])
	{
		height++;
		i++;
	}
	map_data->height = height;
}

void	allocate_grid(char **array, t_map *map_data)
{
	int		j;
	char	**grid;

	j = 0;
	grid = malloc(sizeof(char *) * (map_data->height + 1));
	if (!grid)
	{
		free_map_data(map_data);
		free_array(array);
		error_exit("Failed to malloc grid in get_grid function");
	}
	grid[map_data->height] = NULL;
	while (j < map_data->height)
	{
		grid[j] = malloc(sizeof(char) * (map_data->width + 1));
		if (!grid[j])
		{
			free_map_data(map_data);
			free_array(array);
			error_exit("Failed to malloc grid[j] in get_grid function");
		}
		grid[j][map_data->width] = '\0';
		j++;
	}
	map_data->grid = grid;
}

void	get_map_line(char *array, t_map *map_data, int grid_index)
{
	int	j;
	int	len;

	j = 0;
	len = ft_strlen(array);
	while (j < map_data->width)
	{
		if (j < len)
			map_data->grid[grid_index][j] = array[j];
		else
			map_data->grid[grid_index][j] = ' ';
		j++;
	}
	map_data->grid[grid_index][j] = '\0';
}

t_map	*get_map_data(char *cub_name)
{
	int		i;
	int		j;
	char	**array;
	t_map	*map_data;

	i = 0;
	array = fill_array(cub_name);
	j = find_map_index(array);
	map_data = allocate_map_struct(array);
	get_paths(array, map_data);
	get_color(array, map_data);
	get_width(array, map_data);
	get_height(array, map_data);
	allocate_grid(array, map_data);
	while (i < map_data->height)
	{
		get_map_line(array[j], map_data, i);
		j++;
		i++;
	}
	free_array(array);
	check_all_map_data(map_data);
	return (map_data);
}
