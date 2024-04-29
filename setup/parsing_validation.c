/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_validation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alabdull <@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 19:19:28 by shamzaou          #+#    #+#             */
/*   Updated: 2024/04/29 18:12:56 by alabdull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	are_valid_colors(char **colors)
{
	int	i;

	i = 0;
	while (colors[i])
	{
		if (!is_numeric(colors[i]))
			return (0);
		i++;
	}
	return (i == 3);
}

static int	is_valid_color(t_color *color)
{
	if (color->red < 0 || color->red > 255)
		return (0);
	if (color->green < 0 || color->green > 255)
		return (0);
	if (color->blue < 0 || color->blue > 255)
		return (0);
	return (1);
}

int	validate_colors(t_color *color, char **colors)
{
	if (!are_valid_colors(colors))
	{
		ft_putstr_fd(2, "Error\n");
		ft_putstr_fd(2, "Invalid color format. Please use three \
comma-separated digits for the color components (e.g., 'R,G,B').\n");
		return (WRONG_MAP);
	}
	color->red = ft_atoi(colors[0]);
	color->green = ft_atoi(colors[1]);
	color->blue = ft_atoi(colors[2]);
	if (!is_valid_color(color))
	{
		ft_putstr_fd(2, "Error\n");
		ft_putstr_fd(2, "Color components must be between 0 \
and 255.\n");
		return (WRONG_MAP);
	}
	return (SUCCESS);
}

int	is_valid_texture_path(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (0);
	close(fd);
	return (1);
}
