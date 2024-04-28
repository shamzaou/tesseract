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
	perror("Error\n");
	perror("This line is invalid: ");
	perror(map_line);
	perror("\n");
	return (free_split_array(*array), WRONG_MAP);
}

int	print_missing_elements_error(t_mdata *map_infos)
{
	perror("Error\n");
	perror("Invalid map file. \
Missing elements:\n");
	if (map_infos->no_path_parsed != 1)
		perror("  - NO texture path\n");
	if (map_infos->so_path_parsed != 1)
		perror("  - SO texture path\n");
	if (map_infos->we_path_parsed != 1)
		perror("  - WE texture path\n");
	if (map_infos->ea_path_parsed != 1)
		perror("  - EA texture path\n");
	if (map_infos->floor_color_parsed != 1)
		perror("  - Floor color\n");
	if (map_infos->ceiling_color_parsed != 1)
		perror("  - Ceiling color\n");
	return (WRONG_MAP);
}
