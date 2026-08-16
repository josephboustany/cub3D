/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nassaf <nassaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 21:55:41 by nassaf            #+#    #+#             */
/*   Updated: 2025/12/20 03:39:48 by nassaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	is_space(t_map *map_data, int y, int x)
{
	if (map_data->grid[y][x] == ' ')
		return (1);
	return (0);
}

int	is_player(t_map *map_data, int y, int x)
{
	if (map_data->grid[y][x] == 'N'
		|| map_data->grid[y][x] == 'S'
		|| map_data->grid[y][x] == 'E'
		|| map_data->grid[y][x] == 'W')
		return (1);
	return (0);
}

int	is_floor(t_map *map_data, int y, int x)
{
	if (map_data->grid[y][x] == '0')
		return (1);
	return (0);
}

int	is_wall(t_map *map_data, int y, int x)
{
	if (map_data->grid[y][x] == '1')
		return (1);
	return (0);
}

void	check_map_chars(t_map *map_data)
{
	int	y;
	int	x;

	y = 0;
	while (y < map_data->height)
	{
		x = 0;
		while (map_data->grid[y][x])
		{
			if (!is_space(map_data, y, x)
				&& !is_player(map_data, y, x)
				&& !is_floor(map_data, y, x)
				&& !is_wall(map_data, y, x))
			{
				free_map_data(map_data);
				error_exit("Wrong Chars in MAP - allowed: space,1,0,N,S,E,W");
			}
			x++;
		}
		y++;
	}
}
