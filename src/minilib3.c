/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minilib3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nassaf <nassaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 23:22:55 by nassaf            #+#    #+#             */
/*   Updated: 2026/02/20 04:46:45 by nassaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	close_with_x(t_game *game)
{
	final_exit2(game);
	return (0);
}

void	rotate_player(t_game *game, double dir)
{
	double	old_dir_x;
	double	old_plane_x;
	double	speed;

	speed = R_SPEED * dir;
	old_dir_x = game->dir_x;
	old_plane_x = game->plane_x;
	game->dir_x = game->dir_x * cos(speed) - game->dir_y * sin(speed);
	game->dir_y = old_dir_x * sin(speed) + game->dir_y * cos(speed);
	game->plane_x = game->plane_x * cos(speed) - game->plane_y * sin(speed);
	game->plane_y = old_plane_x * sin(speed) + game->plane_y * cos(speed);
}

void	move_player(t_game *game, double dir)
{
	double	new_x;
	double	new_y;

	new_x = game->pos_x + (game->dir_x * M_SPEED * dir);
	new_y = game->pos_y + (game->dir_y * M_SPEED * dir);
	if (game->grid[(int)game->pos_y][(int)new_x] == '0')
		game->pos_x = new_x;
	if (game->grid[(int)new_y][(int)game->pos_x] == '0')
		game->pos_y = new_y;
}

void	strafe_player(t_game *game, double dir)
{
	double	new_x;
	double	new_y;

	new_x = game->pos_x + (-game->dir_y * M_SPEED * dir);
	new_y = game->pos_y + (game->dir_x * M_SPEED * dir);
	if (game->grid[(int)game->pos_y][(int)new_x] == '0')
		game->pos_x = new_x;
	if (game->grid[(int)new_y][(int)game->pos_x] == '0')
		game->pos_y = new_y;
}

void	start_game(t_game *game)
{
	mlx_hook(game->win, 2, 1L << 0, keyboard_keys, game);
	mlx_hook(game->win, 3, 1L << 1, key_release, game);
	mlx_hook(game->win, 17, 0, close_with_x, game);
	mlx_loop_hook(game->mlx, render_frame, game);
	mlx_loop(game->mlx);
}
