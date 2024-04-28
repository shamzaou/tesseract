/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_mouvements.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamzaou <shamzaou@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 19:27:49 by shamzaou          #+#    #+#             */
/*   Updated: 2024/04/28 19:27:49 by shamzaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	move_up(t_params *params)
{
	int	x;
	int	y;

	x = (int)(params->player.x + params->player.dx * 1.5) / TILE_SIZE;
	y = (int)(params->player.y + params->player.dy * 1.5) / TILE_SIZE;
	if (x >= 0 && x < params->map.cols && y >= 0 && y < params->map.rows
		&& (params->map.map_data[y][x] == '0'))
	{
		params->player.x += params->player.dx;
		params->player.y += params->player.dy;
		cast_rays(params);
	}
}

void	move_down(t_params *params)
{
	int	x;
	int	y;

	x = (int)(params->player.x - params->player.dx) / TILE_SIZE;
	y = (int)(params->player.y - params->player.dy) / TILE_SIZE;
	if (x >= 0 && x < params->map.cols && y >= 0 && y < params->map.rows
		&& params->map.map_data[y][x] == '0')
	{
		params->player.x -= params->player.dx;
		params->player.y -= params->player.dy;
		cast_rays(params);
	}
}

void	move_left(t_params *params)
{
	int		x;
	int		y;
	double	sin_value;
	double	cos_value;

	sin_value = sin(params->player.direction + M_PI / 2) * MOVE_SPEED;
	cos_value = cos(params->player.direction + M_PI / 2) * MOVE_SPEED;
	y = (int)(((params->player.y - sin_value) - 0.0001) / TILE_SIZE);
	x = (int)(((params->player.x - cos_value) - 0.0001) / TILE_SIZE);
	if (x >= 0 && x < params->map.cols && y >= 0 && y < params->map.rows
		&& params->map.map_data[y][x] == '0')
	{
		params->player.x -= cos_value;
		params->player.y -= sin_value;
		cast_rays(params);
	}
}

void	move_right(t_params *params)
{
	int		x;
	int		y;
	double	sin_value;
	double	cos_value;

	sin_value = sin(params->player.direction + M_PI / 2) * MOVE_SPEED;
	cos_value = cos(params->player.direction + M_PI / 2) * MOVE_SPEED;
	y = (int)(((params->player.y + sin_value) - 0.0001) / TILE_SIZE);
	x = (int)(((params->player.x + cos_value) - 0.0001) / TILE_SIZE);
	if (x >= 0 && x < params->map.cols && y >= 0 && y < params->map.rows
		&& params->map.map_data[y][x] == '0')
	{
		params->player.x += cos_value;
		params->player.y += sin_value;
		cast_rays(params);
	}
}
