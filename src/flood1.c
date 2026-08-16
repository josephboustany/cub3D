/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboustan <jboustan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 02:23:36 by nassaf            #+#    #+#             */
/*   Updated: 2026/05/25 00:59:45 by jboustan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_check	*create_map_check(t_map *map_data)
{
	t_check	*map_check;

	check_map_chars(map_data);
	check_if_one_player(map_data);
	map_check = alloc_map_check(map_data);
	locate_player(map_data, map_check);
	duplicate_map(map_data, map_check);
	return (map_check);
}

int	check_up(t_check *map_check, int x, int y, t_map *map_data)
{
	char	c;

	if (y - 1 < 0)
		free_exit2(map_data, map_check, "Invalid Map - Open Boundary");
	c = map_check->map_dup[y - 1][x];
	//the fix starts here,refer to flood_fill_open_boundary.md
	if (c == ' ')
		free_exit2(map_data, map_check, "Invalid Map - Open Boundary");
	//end of fix
	if (c != '0' && c != '1' && c != '2' && c != ' '
		&& c != 'N' && c != 'S' && c != 'E' && c != 'W')
		free_exit2(map_data, map_check, "Invalid Map - Invalid Character");
	if (c == '0')
		return (1);
	return (0);
}

int	check_down(t_check *map_check, int x, int y, t_map *map_data)
{
	char	c;

	if (y + 1 >= map_data->height)
		free_exit2 (map_data, map_check, "Invalid Map - Open Boundary");
	c = map_check->map_dup[y + 1][x];
	//the fix starts here, refer to flood_fill_open_boundary.md
	if (c == ' ')
		free_exit2(map_data, map_check, "Invalid Map - Open Boundary");
	//end of fix
	if (c != '0' && c != '1' && c != '2' && c != ' '
		&& c != 'N' && c != 'S' && c != 'E' && c != 'W')
		free_exit2 (map_data, map_check, "Invalid map - Invalid Character");
	if (c == '0')
		return (1);
	return (0);
}

int	check_left(t_check *map_check, int x, int y, t_map *map_data)
{
	char	c;

	if (x - 1 < 0)
		free_exit2 (map_data, map_check, "Invalid Map - Open Boundary");
	c = map_check->map_dup[y][x - 1];
	//the fix starts here, refer to flood_fill_open_boundary.md
	if (c == ' ')
		free_exit2(map_data, map_check, "Invalid Map - Open Boundary");
	//end of fix
	if (c != '0' && c != '1' && c != '2' && c != ' '
		&& c != 'N' && c != 'S' && c != 'E' && c != 'W')
		free_exit2(map_data, map_check, "Invalid Map - Invalid Character");
	if (c == '0')
		return (1);
	return (0);
}

int	check_right(t_check *map_check, int x, int y, t_map *map_data)
{
	char	c;

	if (x + 1 >= map_data->width)
		free_exit2 (map_data, map_check, "Invalid Map - Open Boundary");
	c = map_check->map_dup[y][x + 1];
	//the fix starts here, refer to flood_fill_open_boundary.md
	if (c == ' ')
		free_exit2(map_data, map_check, "Invalid Map - Open Boundary");
	//end of fix
	if (c != '0' && c != '1' && c != '2' && c != ' '
		&& c != 'N' && c != 'S' && c != 'E' && c != 'W')
		free_exit2(map_data, map_check, "Invalid map - Invalid Character");
	if (c == '0')
		return (1);
	return (0);
}
