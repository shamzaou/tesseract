/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamzaou <shamzaou@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 19:28:27 by shamzaou          #+#    #+#             */
/*   Updated: 2024/04/28 19:28:27 by shamzaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	get_horizontal_texture(t_params *params, t_ray *ray,
		t_wall *wall)
{
	t_point	index;

	wall->texture_x = (int)ray->x % TILE_SIZE;
	if (ray->direction > M_PI)
		wall->texture_x = TILE_SIZE - wall->texture_x - 1;
	index.x = (int)(ray->x) / TILE_SIZE;
	index.y = (int)(ray->y - 0.00001) / TILE_SIZE;
	if (params->map.map_data[index.y][index.x] == '1')
	{
		wall->wall_texture = params->north_texture.addr;
		wall->texture_img = &params->north_texture;
	}
	else
	{
		wall->wall_texture = params->south_texture.addr;
		wall->texture_img = &params->south_texture;
	}
}

static void	get_vertical_texture(t_params *params, t_ray *ray,
		t_wall *wall)
{
	t_point	index;

	wall->texture_x = (int)ray->y % TILE_SIZE;
	if (ray->direction > M_PI / 2 && ray->direction < 3 * M_PI / 2)
		wall->texture_x = TILE_SIZE - wall->texture_x - 1;
	index.x = (int)(ray->x - 0.00001) / TILE_SIZE;
	index.y = (int)ray->y / TILE_SIZE;
	if (params->map.map_data[index.y][index.x] == '1')
	{
		wall->wall_texture = params->west_texture.addr;
		wall->texture_img = &params->west_texture;
	}
	else
	{
		wall->wall_texture = params->east_texture.addr;
		wall->texture_img = &params->east_texture;
	}
}

void	get_wall_texture(t_params *params, t_ray *ray, t_wall *wall)
{
	wall->wall_height = (WINDOW_HEIGHT * TILE_SIZE) / ray->length;
	wall->wall_y = (WINDOW_HEIGHT / 2) - (wall->wall_height / 2);
	if (ray->hit == HORIZONTAL)
		get_horizontal_texture(params, ray, wall);
	else
		get_vertical_texture(params, ray, wall);
}

void	render_wall_texture(t_params *params, t_wall *wall, int column)
{
	int		y;
	int		pixel_index;
	int		hex_color;
	double	texture_pos;
	double	texture_step;

	y = 0;
	texture_pos = 0;
	texture_step = TEXTURE_SIZE / wall->wall_height;
	while (y < wall->wall_height)
	{
		wall->texture_y = (int)texture_pos & (TEXTURE_SIZE - 1);
		pixel_index = ((int)wall->texture_y * TEXTURE_SIZE
				+ (int)wall->texture_x) * wall->texture_img->bpp;
		hex_color = *(unsigned int *)(wall->wall_texture + pixel_index);
		mlx_pixel_put_img(params, column, wall->wall_y + y, hex_color);
		texture_pos += texture_step;
		y++;
	}
}

void	render_ground_and_ceiling(t_params *params, t_wall *wall, int column)
{
	draw_line_img(params, init_point(column, wall->wall_y + wall->wall_height),
		init_point(column, WINDOW_HEIGHT), params->floor_color);
	draw_line_img(params, init_point(column, 0), init_point(column,
			wall->wall_y), params->ceiling_color);
}
