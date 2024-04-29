/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_error_handling.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alabdull <@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 19:18:45 by shamzaou          #+#    #+#             */
/*   Updated: 2024/04/29 18:12:56 by alabdull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	handle_invalid_line(char ***array, char *map_line)
{
	ft_putstr_fd(2, "Error\n");
	ft_putstr_fd(2, "This line is invalid: ");
	ft_putstr_fd(2, map_line);
	ft_putstr_fd(2, "\n");
	return (free_split_array(*array), WRONG_MAP);
}

int	print_missing_elements_error(t_mdata *map_infos)
{
	ft_putstr_fd(2, "Error\n");
	ft_putstr_fd(2, "Invalid map file. \
Missing elements:\n");
	if (map_infos->no_path_parsed != 1)
		ft_putstr_fd(2, "  - NO texture path\n");
	if (map_infos->so_path_parsed != 1)
		ft_putstr_fd(2, "  - SO texture path\n");
	if (map_infos->we_path_parsed != 1)
		ft_putstr_fd(2, "  - WE texture path\n");
	if (map_infos->ea_path_parsed != 1)
		ft_putstr_fd(2, "  - EA texture path\n");
	if (map_infos->floor_color_parsed != 1)
		ft_putstr_fd(2, "  - Floor color\n");
	if (map_infos->ceiling_color_parsed != 1)
		ft_putstr_fd(2, "  - Ceiling color\n");
	return (WRONG_MAP);
}
