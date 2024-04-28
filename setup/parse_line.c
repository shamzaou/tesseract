/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamzaou <shamzaou@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 19:19:15 by shamzaou          #+#    #+#             */
/*   Updated: 2024/04/28 19:19:15 by shamzaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	parse_texture_line(t_mdata *map_infos, char **array)
{
	if (array_size(array) != 2)
	{
		perror("Error\n");
		perror("Invalid texture line format. Please provide \
only the texture identifier and the path.\n");
		return (WRONG_MAP);
	}
	if (!is_valid_texture_path(array[1]))
	{
		perror("Error\n");
		perror("Invalid or non-existent texture path. Please provide \
a valid and accessible file path for the texture.\n");
		return (WRONG_MAP);
	}
	if (ft_strcmp(array[0], "NO") == 0)
		map_infos->no_path = ft_strdup(array[1]);
	else if (ft_strcmp(array[0], "SO") == 0)
		map_infos->so_path = ft_strdup(array[1]);
	else if (ft_strcmp(array[0], "WE") == 0)
		map_infos->we_path = ft_strdup(array[1]);
	else if (ft_strcmp(array[0], "EA") == 0)
		map_infos->ea_path = ft_strdup(array[1]);
	return (SUCCESS);
}

static int	count_commas(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == ',')
			count++;
		i++;
	}
	return (count);
}

static int	parse_color_line(t_mdata *map_infos, char **array)
{
	char	**colors;
	t_color	*color;

	if (array_size(array) != 2)
		return (perror("Error\n"), \
		perror("Invalid color line format. Please provide \
only the color identifier and the color components.\n"), WRONG_MAP);
	if (ft_strcmp(array[0], "F") == 0)
		color = &map_infos->floor_color;
	else if (ft_strcmp(array[0], "C") == 0)
		color = &map_infos->ceiling_color;
	if (count_commas(array[1]) != 2)
	{
		perror("Error\n");
		perror("Invalid color format. Please use three \
comma-separated digits for the color components (e.g., 'R,G,B').\n");
		return (WRONG_MAP);
	}
	colors = ft_split(array[1], ',');
	if (validate_colors(color, colors) == WRONG_MAP)
		return (free_split_array(colors), WRONG_MAP);
	free_split_array(colors);
	return (SUCCESS);
}

int	handle_texture_line(t_mdata *map_infos, char ***array,
							int *parsed_flag, char *type)
{
	if (*parsed_flag)
	{
		ft_printf_fd(2, "Error\n");
		ft_printf_fd(2, "Duplicate %s texture path.\n", type);
		return (free_split_array(*array), WRONG_MAP);
	}
	else
	{
		if (parse_texture_line(map_infos, *array) != SUCCESS)
			return (free_split_array(*array), WRONG_MAP);
		*parsed_flag = 1;
	}
	return (free_split_array(*array), SUCCESS);
}

int	handle_color_line(t_mdata *map_infos, char ***array,
						int *parsed_flag, char *type)
{
	if (*parsed_flag)
	{
		ft_printf_fd(2, "Error\n");
		ft_printf_fd(2, "Duplicate %s color.\n", type);
		return (free_split_array(*array), WRONG_MAP);
	}
	else
	{
		if (parse_color_line(map_infos, *array) != SUCCESS)
			return (free_split_array(*array), WRONG_MAP);
		*parsed_flag = 1;
	}
	return (free_split_array(*array), SUCCESS);
}
