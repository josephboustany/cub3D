/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minilib2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nassaf <nassaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 22:52:12 by nassaf            #+#    #+#             */
/*   Updated: 2026/02/20 04:44:12 by nassaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	set_north_south(t_game *game, char c)
{
	if (c == 'N')
	{
		game->dir_x = 0;
		game->dir_y = -1;
		game->plane_x = 0.66;
		game->plane_y = 0;
	}
	else
	{
		game->dir_x = 0;
		game->dir_y = 1;
		game->plane_x = -0.66;
		game->plane_y = 0;
	}
}

void	set_east_west(t_game *game, char c)
{
	if (c == 'E')
	{
		game->dir_x = 1;
		game->dir_y = 0;
		game->plane_x = 0;
		game->plane_y = 0.66;
	}
	else
	{
		game->dir_x = -1;
		game->dir_y = 0;
		game->plane_x = 0;
		game->plane_y = -0.66;
	}
}

void	set_direction(t_game *game, char c)
{
	if (c == 'N' || c == 'S')
		set_north_south(game, c);
	else if (c == 'E' || c == 'W')
		set_east_west(game, c);
}

void	set_player_pos(t_map *map_data, t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (map_data->grid[y])
	{
		x = 0;
		while (map_data->grid[y][x])
		{
			if (map_data->grid[y][x] == 'N' || map_data->grid[y][x] == 'S' ||
				map_data->grid[y][x] == 'E' || map_data->grid[y][x] == 'W')
			{
				game->pos_x = x + 0.5;
				game->pos_y = y + 0.5;
				set_direction(game, map_data->grid[y][x]);
				map_data->grid[y][x] = '0';
				return ;
			}
			x++;
		}
		y++;
	}
}

int	keyboard_keys(int keycode, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (keycode == K_ESC)
		final_exit2(game);
	if (keycode == K_W)
		game->keys[0] = 1;
	if (keycode == K_S)
		game->keys[1] = 1;
	if (keycode == K_A)
		game->keys[2] = 1;
	if (keycode == K_D)
		game->keys[3] = 1;
	if (keycode == K_LEFT)
		game->keys[4] = 1;
	if (keycode == K_RIGHT)
		game->keys[5] = 1;
	return (0);
}
