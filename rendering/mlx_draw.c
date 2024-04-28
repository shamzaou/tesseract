/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_draw.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamzaou <shamzaou@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 19:27:55 by shamzaou          #+#    #+#             */
/*   Updated: 2024/04/28 19:27:55 by shamzaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

t_point	init_point(int x, int y)
{
	t_point	point;

	point.x = x;
	point.y = y;
	return (point);
}

int	mlx_pixel_put_img(t_params *params, int x, int y, int color)
{
	int	pixel_index;

	pixel_index = y * params->window_img.line_length
		+ x * params->window_img.bpp;
	if (pixel_index >= 0 && pixel_index < params->window_img.line_length
		* params->window_img.height)
		*(unsigned int *)(params->window_img.addr + pixel_index) = color;
	return (0);
}

void	my_mlx_pixel_put(t_gdata *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}