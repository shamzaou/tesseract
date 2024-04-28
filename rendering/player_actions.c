/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_actions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamzaou <shamzaou@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 19:27:40 by shamzaou          #+#    #+#             */
/*   Updated: 2024/04/28 19:27:40 by shamzaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	normalize_direction(double *direction)
{
	if (*direction < 0)
		*direction += 2 * M_PI;
	if (*direction > 2 * M_PI)
		*direction -= 2 * M_PI;
}

void	look_left(t_params *params)
{
	params->player.direction -= ROTATE_SPEED;
	normalize_direction(&params->player.direction);
	params->player.dx = cos(params->player.direction) * MOVE_SPEED;
	params->player.dy = sin(params->player.direction) * MOVE_SPEED;
	cast_rays(params);
}

void	look_right(t_params *params)
{
	params->player.direction += ROTATE_SPEED;
	normalize_direction(&params->player.direction);
	params->player.dx = cos(params->player.direction) * MOVE_SPEED;
	params->player.dy = sin(params->player.direction) * MOVE_SPEED;
	cast_rays(params);
}
