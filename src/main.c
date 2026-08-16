/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nassaf <nassaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 22:36:05 by nassaf            #+#    #+#             */
/*   Updated: 2026/02/20 05:00:37 by nassaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main(int argc, char **argv)
{
	t_map	*map_data;
	t_game	*game;

	validate_args(argc, argv);
	map_data = get_map_data(argv[1]);
	validate_map(map_data);
	game = create_t_game(map_data);
	game->mlx = mlx_init();
	if (!game->mlx)
		final_exit(game, "MLX init failed");
	game->win = mlx_new_window(game->mlx, SCREEN_W, SCREEN_H, "cub3D");
	if (!game->win)
		final_exit(game, "Window creation failed");
	set_player_pos(map_data, game);
	load_textures(map_data, game);
	init_screen_buffer(game);
	start_game(game);
	return (0);
}
