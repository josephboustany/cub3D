/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nassaf <nassaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 01:00:14 by nassaf            #+#    #+#             */
/*   Updated: 2026/02/20 01:18:19 by nassaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	free_map_data(t_map *map_data)
{
	int	i;

	i = 0;
	if (map_data->grid)
	{
		while (map_data->grid[i])
		{
			free(map_data->grid[i]);
			i++;
		}
		free (map_data->grid);
	}
	if (map_data->north_texture)
		free(map_data->north_texture);
	if (map_data->south_texture)
		free(map_data->south_texture);
	if (map_data->east_texture)
		free(map_data->east_texture);
	if (map_data->west_texture)
		free (map_data->west_texture);
	free(map_data);
}

void	free_and_exit(t_map *map_data, char *message)
{
	free_map_data(map_data);
	error_exit(message);
}

void	free_exit2(t_map *map_data, t_check *map_check, char *message)
{
	int	i;

	i = 0;
	if (map_check)
	{
		if (map_check->map_dup)
		{
			while (i < map_data->height)
			{
				free(map_check->map_dup[i]);
				i++;
			}
			free(map_check->map_dup);
		}
		if (map_check->pos_x)
			free(map_check->pos_x);
		if (map_check->pos_y)
			free(map_check->pos_y);
		free(map_check);
	}
	if (map_data)
		free_map_data(map_data);
	if (message)
		error_exit(message);
}

void	final_exit(t_game *game, char *message)
{
	if (game->grid)
		free_array(game->grid);
	if (game->north.img)
		mlx_destroy_image(game->mlx, game->north.img);
	if (game->south.img)
		mlx_destroy_image(game->mlx, game->south.img);
	if (game->east.img)
		mlx_destroy_image(game->mlx, game->east.img);
	if (game->west.img)
		mlx_destroy_image(game->mlx, game->west.img);
	if (game->screen.img)
		mlx_destroy_image(game->mlx, game->screen.img);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free (game->mlx);
	}
	free (game);
	error_exit (message);
}

void	final_exit2(t_game *game)
{
	if (game->grid)
		free_array(game->grid);
	if (game->north.img)
		mlx_destroy_image(game->mlx, game->north.img);
	if (game->south.img)
		mlx_destroy_image(game->mlx, game->south.img);
	if (game->east.img)
		mlx_destroy_image(game->mlx, game->east.img);
	if (game->west.img)
		mlx_destroy_image(game->mlx, game->west.img);
	if (game->screen.img)
		mlx_destroy_image(game->mlx, game->screen.img);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	free(game);
	exit(0);
}
