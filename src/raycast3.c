/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboustan <jboustan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 10:21:03 by jboustan          #+#    #+#             */
/*   Updated: 2026/05/23 12:50:19 by jboustan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw_wall_strip(t_game *game, t_ray *ray, t_tex *tex, int x)
{
	int	tex_x;
	int	tex_y;
	int	y;

	tex_x = get_tex_x(game, ray, tex);
	y = ray->draw_start;
	while (y <= ray->draw_end)
	{
		tex_y = ((y - SCREEN_H / 2 + ray->line_height / 2)
				* tex->height) / ray->line_height;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= tex->height)
			tex_y = tex->height - 1;
		pixel_put(&game->screen, x, y, tex->addr[tex_y * tex->width + tex_x]);
		y++;
	}
}

void	draw_column(t_game *game, t_ray *ray, int x)
{
	t_tex	*tex;

	tex = get_tex(game, ray);
	calc_draw_range(ray);
	draw_ceiling_floor(game, ray, x);
	draw_wall_strip(game, ray, tex, x);
}
