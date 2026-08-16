/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nassaf <nassaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 16:27:53 by nassaf            #+#    #+#             */
/*   Updated: 2026/02/10 00:21:41 by nassaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	final_check(t_check *map_check, t_map *map_data)
{
	int	y;
	int	x;

	y = 0;
	while (y < map_data->height)
	{
		x = 0;
		while (x < map_data->width)
		{
			if (map_check->map_dup[y][x] == '0')
			{
				if (y == 0 || y == map_data->height - 1
					|| x == 0 || x == map_data->width - 1)
					free_exit2(map_data, map_check, "Open Boundary");
				if (map_check->map_dup[y - 1][x] == ' '
					|| map_check->map_dup[y + 1][x] == ' '
					|| map_check->map_dup[y][x - 1] == ' '
					|| map_check->map_dup[y][x + 1] == ' ')
					free_exit2(map_data, map_check, "Open Boundary");
			}
			x++;
		}
		y++;
	}
}

void	mark_as_visited(t_check *map_check, int x, int y)
{
	map_check->map_dup[y][x] = '2';
}

void	add_to_list(t_check *map_check, int x, int y)
{
	if (map_check->map_dup[y][x] != '2')
	{
		map_check->map_dup[y][x] = '2';
		map_check->pos_x[map_check->end] = x;
		map_check->pos_y[map_check->end] = y;
		map_check->end++;
	}
}

int	flood_fill(t_check *map_check, t_map *map_data)
{
	int	x;
	int	y;

	while (map_check->start < map_check->end)
	{
		x = map_check->pos_x[map_check->start];
		y = map_check->pos_y[map_check->start];
		mark_as_visited(map_check, x, y);
		if (check_up(map_check, x, y, map_data) == 1)
			add_to_list(map_check, x, y - 1);
		if (check_down(map_check, x, y, map_data) == 1)
			add_to_list(map_check, x, y + 1);
		if (check_left(map_check, x, y, map_data) == 1)
			add_to_list(map_check, x - 1, y);
		if (check_right(map_check, x, y, map_data) == 1)
			add_to_list(map_check, x + 1, y);
		map_check->start++;
	}
	return (0);
}

void	validate_map(t_map *map_data)
{
	t_check	*map_check;
	int		i;

	map_check = create_map_check(map_data);
	flood_fill(map_check, map_data);
	final_check(map_check, map_data);
	i = 0;
	while (i < map_data->height)
		free(map_check->map_dup[i++]);
	free(map_check->map_dup);
	free(map_check->pos_x);
	free(map_check->pos_y);
	free(map_check);
}
