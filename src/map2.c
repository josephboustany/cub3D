/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nassaf <nassaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 03:30:14 by nassaf            #+#    #+#             */
/*   Updated: 2026/02/09 23:49:00 by nassaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	check_if_one_player(t_map *map_data)
{
	int	y;
	int	x;
	int	p;

	y = 0;
	p = 0;
	while (y < map_data->height)
	{
		x = 0;
		while (map_data->grid[y][x])
		{
			if (is_player(map_data, y, x))
				p++;
			x++;
		}
		y++;
	}
	if (p > 1 || p == 0)
	{
		free_map_data(map_data);
		error_exit("One and only 1 player should exist");
	}
}

char	**alloc_map_dup(t_map *map_data)
{
	int		j;
	char	**duplicated_map;

	duplicated_map = malloc(sizeof(char *) * (map_data->height + 1));
	if (!duplicated_map)
		free_and_exit(map_data, "Malloc1 failed in duplicate_map()");
	j = 0;
	while (j < map_data->height)
	{
		duplicated_map[j] = malloc(sizeof(char) * (map_data->width + 1));
		if (!duplicated_map[j])
			free_and_exit(map_data, "Malloc2 failed in duplicate_map()");
		j++;
	}
	return (duplicated_map);
}

t_check	*alloc_map_check(t_map *map_data)
{
	t_check	*map_check;
	int		i;

	i = 0;
	map_check = malloc(sizeof(t_check));
	if (!map_check)
		free_and_exit(map_data, "Malloc1 failed in alloc_map_check()");
	map_check->pos_x = malloc(sizeof(int) * map_data->height * map_data->width);
	map_check->pos_y = malloc(sizeof(int) * map_data->height * map_data->width);
	if (!map_check->pos_x || !map_check->pos_y)
		free_exit2(map_data, map_check, "Malloc2 in alloc_map_check()");
	map_check->map_dup = alloc_map_dup(map_data);
	while (i < map_data->height * map_data->width)
	{
		map_check->pos_x[i] = 0;
		map_check->pos_y[i] = 0;
		i++;
	}
	map_check->start = 0;
	map_check->end = 0;
	return (map_check);
}

void	locate_player(t_map *map_data, t_check *map_check)
{
	int	y;
	int	x;

	y = 0;
	while (y < map_data->height)
	{
		x = 0;
		while (x < map_data->width)
		{
			if (is_player(map_data, y, x))
			{
				if (x == 0 || x == map_data->width - 1
					|| y == 0 || y == map_data->height - 1)
					free_exit2(map_data, map_check, "Player on edge");
				map_check->pos_x[0] = x;
				map_check->pos_y[0] = y;
			}
			x++;
		}
		y++;
	}
	map_check->start = 0;
	map_check->end = 1;
}

void	duplicate_map(t_map *map_data, t_check *map_check)
{
	int	i;
	int	j;

	j = 0;
	while (j < map_data->height)
	{
		i = 0;
		while (i < map_data->width)
		{
			map_check->map_dup[j][i] = map_data->grid[j][i];
			i++;
		}
		map_check->map_dup[j][i] = '\0';
		j++;
	}
}
