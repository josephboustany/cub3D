/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minilib1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nassaf <nassaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 03:06:25 by nassaf            #+#    #+#             */
/*   Updated: 2026/02/22 20:09:19 by nassaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_game	*create_t_game(t_map *map_data)
{
	t_game	*game;
	int		i;

	game = malloc(sizeof(t_game));
	if (!game)
		free_and_exit(map_data, "Failed to malloc t_game structure");
	game->grid = NULL;
	game->mlx = NULL;
	game->win = NULL;
	game->north.img = NULL;
	game->south.img = NULL;
	game->east.img = NULL;
	game->west.img = NULL;
	game->screen.img = NULL;
	game->pos_x = 0;
	game->pos_y = 0;
	game->dir_x = 0;
	game->dir_y = 0;
	game->plane_x = 0;
	game->plane_y = 0;
	i = 0;
	while (i < 6)
		game->keys[i++] = 0;
	return (game);
}

void	load_texture(t_game *game, t_tex *tex, char *path)
{
	tex->img = mlx_xpm_file_to_image(game->mlx, path,
			&tex->width, &tex->height);
	if (!tex->img)
		final_exit(game, "Failed to load texture");
	tex->addr = (int *)mlx_get_data_addr(tex->img, &tex->bpp,
			&tex->line_len, &tex->endian);
}

void	load_textures(t_map *map_data, t_game *game)
{
	load_texture(game, &game->north, map_data->north_texture);
	load_texture(game, &game->south, map_data->south_texture);
	load_texture(game, &game->east, map_data->east_texture);
	load_texture(game, &game->west, map_data->west_texture);
	game->grid = map_data->grid;
	game->floor_color = map_data->floor_color;
	game->ceiling_color = map_data->ceiling_color;
	map_data->grid = NULL;
	free_map_data(map_data);
}

void	pixel_put(t_tex *screen, int x, int y, int color)
{
	char	*dst;

	dst = (char *)screen->addr + (y * screen->line_len + x * (screen->bpp / 8));
	*(unsigned int *)dst = color;
}

void	init_screen_buffer(t_game *game)
{
	game->screen.img = mlx_new_image(game->mlx, SCREEN_W, SCREEN_H);
	game->screen.addr = (int *)mlx_get_data_addr(game->screen.img,
			&game->screen.bpp, &game->screen.line_len, &game->screen.endian);
}
