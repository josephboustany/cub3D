/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minilib4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nassaf <nassaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 20:45:15 by nassaf            #+#    #+#             */
/*   Updated: 2026/02/22 20:45:20 by nassaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	key_release(int keycode, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (keycode == K_W)
		game->keys[0] = 0;
	if (keycode == K_S)
		game->keys[1] = 0;
	if (keycode == K_A)
		game->keys[2] = 0;
	if (keycode == K_D)
		game->keys[3] = 0;
	if (keycode == K_LEFT)
		game->keys[4] = 0;
	if (keycode == K_RIGHT)
		game->keys[5] = 0;
	return (0);
}

void	process_keys(t_game *game)
{
	if (game->keys[0])
		move_player(game, 1);
	if (game->keys[1])
		move_player(game, -1);
	if (game->keys[2])
		strafe_player(game, -1);
	if (game->keys[3])
		strafe_player(game, 1);
	if (game->keys[4])
		rotate_player(game, -1);
	if (game->keys[5])
		rotate_player(game, 1);
}
