/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing6.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nassaf <nassaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 02:13:40 by nassaf            #+#    #+#             */
/*   Updated: 2026/02/09 23:31:32 by nassaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	validate_texture_path(char *path, char *error, t_map *map_data)
{
	int	len;
	int	fd;

	len = ft_strlen(path);
	if (len < 4)
		free_and_exit(map_data, error);
	if (path[len -1] != 'm' || path[len - 2] != 'p'
		|| path[len - 3] != 'x' || path[len - 4] != '.')
		free_and_exit(map_data, "Wrong ext for textures. Not xpm");
	fd = open(path, O_RDONLY);
	if (fd == -1)
		free_and_exit(map_data, error);
	close(fd);
}

void	check_paths(t_map *map_data)
{
	validate_texture_path(map_data->north_texture,
		"North texture path is invalid", map_data);
	validate_texture_path(map_data->south_texture,
		"South texture path is invalid", map_data);
	validate_texture_path(map_data->east_texture,
		"East texture path is invalid", map_data);
	validate_texture_path(map_data->west_texture,
		"West texture path is invalid", map_data);
}

void	check_all_map_data(t_map *map_data)
{
	if (!map_data->north_texture)
		free_and_exit(map_data, "Missing north texture");
	if (!map_data->south_texture)
		free_and_exit(map_data, "Missing south texture");
	if (!map_data->east_texture)
		free_and_exit(map_data, "Missing east texture");
	if (!map_data->west_texture)
		free_and_exit(map_data, "Missing west texture");
	if (map_data->floor_color == -1)
		free_and_exit(map_data, "Missing floor color");
	if (map_data->ceiling_color == -1)
		free_and_exit(map_data, "Missing ceiling color");
	if (!map_data->grid)
		free_and_exit(map_data, "Missing map grid");
	check_paths(map_data);
}
