/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_error_handling.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamzaou <shamzaou@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 19:18:45 by shamzaou          #+#    #+#             */
/*   Updated: 2024/04/28 19:18:45 by shamzaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	handle_invalid_line(char ***array, char *map_line)
{
	ft_printf_fd(2, "Error\n");
	ft_printf_fd(2, "This line is invalid: {%s}\n", map_line);
	ft_printf_fd(2, "Please provide a valid line.\n");
	return (free_split_array(*array), WRONG_MAP);
}

int	print_missing_elements_error(t_mdata *map_infos)
{
	ft_printf_fd(2, "Error\n");
	ft_printf_fd(2, "Invalid map file. \
The following elements are missing:\n");
	if (map_infos->no_path_parsed != 1)
		ft_printf_fd(2, "  - NO texture path\n");
	if (map_infos->so_path_parsed != 1)
		ft_printf_fd(2, "  - SO texture path\n");
	if (map_infos->we_path_parsed != 1)
		ft_printf_fd(2, "  - WE texture path\n");
	if (map_infos->ea_path_parsed != 1)
		ft_printf_fd(2, "  - EA texture path\n");
	if (map_infos->floor_color_parsed != 1)
		ft_printf_fd(2, "  - Floor color\n");
	if (map_infos->ceiling_color_parsed != 1)
		ft_printf_fd(2, "  - Ceiling color\n");
	return (WRONG_MAP);
}
