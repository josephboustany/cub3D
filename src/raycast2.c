/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboustan <jboustan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 10:20:32 by jboustan          #+#    #+#             */
/*   Updated: 2026/05/23 12:50:11 by jboustan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	cast_ray(t_game *game, t_ray *ray, int x)
{
	init_ray(game, ray, x);
	dda_setup(game, ray);
	dda_run(game, ray);
	get_wall_dist(ray);
	draw_column(game, ray, x);
}

t_tex	*get_tex(t_game *game, t_ray *ray)
{
	if (ray->side == 0 && ray->step_x > 0)
		return (&game->east);
	if (ray->side == 0 && ray->step_x < 0)
		return (&game->west);
	if (ray->side == 1 && ray->step_y > 0)
		return (&game->south);
	return (&game->north);
}

int	get_tex_x(t_game *game, t_ray *ray, t_tex *tex)
{
	int		tex_x;
	double	wall_x;

	if (ray->side == 0)
		wall_x = game->pos_y + ray->perp_wall_dist * ray->ray_dir_y;
	else
		wall_x = game->pos_x + ray->perp_wall_dist * ray->ray_dir_x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * tex->width);
	if (ray->side == 0 && ray->step_x > 0)
		tex_x = tex->width - tex_x - 1;
	if (ray->side == 1 && ray->step_y < 0)
		tex_x = tex->width - tex_x -1;
	return (tex_x);
}

void	calc_draw_range(t_ray *ray)
{
	ray->line_height = (int)((SCREEN_H) / ray->perp_wall_dist);
	ray->draw_start = SCREEN_H / 2 - ray->line_height / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = SCREEN_H / 2 + ray->line_height / 2;
	if (ray->draw_end >= SCREEN_H)
		ray->draw_end = SCREEN_H - 1;
}

void	draw_ceiling_floor(t_game *game, t_ray *ray, int x)
{
	int	y;

	y = 0;
	while (y < ray->draw_start)
		pixel_put(&game->screen, x, y++, game->ceiling_color);
	y = ray->draw_end + 1;
	while (y < SCREEN_H)
		pixel_put(&game->screen, x, y++, game->floor_color);
}
