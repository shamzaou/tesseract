/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamzaou <shamzaou@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 19:18:20 by shamzaou          #+#    #+#             */
/*   Updated: 2024/04/28 19:18:20 by shamzaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	init_bresenham_params(t_point p1, t_point p2, t_point *delta,
									t_point *sign)
{
	delta->x = abs(p2.x - p1.x);
	delta->y = -abs(p2.y - p1.y);
	if (p1.x < p2.x)
		sign->x = 1;
	else
		sign->x = -1;
	if (p1.y < p2.y)
		sign->y = 1;
	else
		sign->y = -1;
}

void	draw_line(t_params *params, t_point p1, t_point p2, int color)
{
	t_point	delta;
	t_point	sign;
	int		err;
	int		e2;

	init_bresenham_params(p1, p2, &delta, &sign);
	err = delta.x + delta.y;
	while (1)
	{
		mlx_pixel_put(params->mlx, params->win, p1.x, p1.y, color);
		if (p1.x == p2.x && p1.y == p2.y)
			break ;
		e2 = 2 * err;
		if (e2 >= delta.y)
		{
			err += delta.y;
			p1.x += sign.x;
		}
		if (e2 <= delta.x)
		{
			err += delta.x;
			p1.y += sign.y;
		}
	}
}

void	draw_line_img(t_params *params, t_point p1, t_point p2, int color)
{
	t_point	delta;
	t_point	sign;
	int		err;
	int		e2;

	init_bresenham_params(p1, p2, &delta, &sign);
	err = delta.x + delta.y;
	while (1)
	{
		mlx_pixel_put_img(params, p1.x, p1.y, color);
		if (p1.x == p2.x && p1.y == p2.y)
			break ;
		e2 = 2 * err;
		if (e2 >= delta.y)
		{
			err += delta.y;
			p1.x += sign.x;
		}
		if (e2 <= delta.x)
		{
			err += delta.x;
			p1.y += sign.y;
		}
	}
}
