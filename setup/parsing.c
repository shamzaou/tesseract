/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamzaou <shamzaou@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 19:19:34 by shamzaou          #+#    #+#             */
/*   Updated: 2024/04/28 19:19:34 by shamzaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	parse_map_to_queue(int fd, t_queue *q)
{
	char	*line;

	init_queue(q);
	line = get_next_line(fd);
	while (line && is_empty_line(line))
	{
		ft_free((void **)&line);
		line = get_next_line(fd);
	}
	while (line && !is_empty_line(line))
	{
		enqueue(q, ft_strtrim(line, "\n"));
		ft_free((void **)&line);
		line = get_next_line(fd);
	}
	ft_free((void **)&line);
}

static int	parse_line(t_mdata *map_infos, char *map_line)
{
	char	**array;

	array = ft_split(map_line, ' ');
	if (startswith(array, "NO"))
		return (handle_texture_line(map_infos, &array,
				&map_infos->no_path_parsed, "NO"));
	else if (startswith(array, "SO"))
		return (handle_texture_line(map_infos, &array,
				&map_infos->so_path_parsed, "SO"));
	else if (startswith(array, "WE"))
		return (handle_texture_line(map_infos, &array,
				&map_infos->we_path_parsed, "WE"));
	else if (startswith(array, "EA"))
		return (handle_texture_line(map_infos, &array,
				&map_infos->ea_path_parsed, "EA"));
	else if (startswith(array, "F"))
		return (handle_color_line(map_infos, &array,
				&map_infos->floor_color_parsed, "floor"));
	else if (startswith(array, "C"))
		return (handle_color_line(map_infos, &array,
				&map_infos->ceiling_color_parsed, "ceiling"));
	else
		return (handle_invalid_line(&array, map_line));
}

int	all_elements_parsed(t_mdata *map_infos)
{
	if (map_infos->no_path_parsed == 1 && map_infos->so_path_parsed == 1
		&& map_infos->we_path_parsed == 1 && map_infos->ea_path_parsed == 1
		&& map_infos->floor_color_parsed == 1
		&& map_infos->ceiling_color_parsed == 1)
		return (1);
	return (0);
}

int	parse_map(char *file_name, t_mdata *map_infos)
{
	int		fd;
	char	*line;
	char	*map_line;

	fd = open_map_file(file_name);
	if (fd == -1)
		return (perror("Error\nCould not open file\n"), OPEN_ERR);
	line = get_next_line(fd);
	while (line)
	{
		map_line = ft_strtrim(line, " \t\v\f\r\n");
		ft_free((void **)&line);
		if (*map_line && parse_line(map_infos, map_line) != SUCCESS)
			return (ft_free((void **)&map_line), close(fd), WRONG_MAP);
		ft_free((void **)&map_line);
		if (all_elements_parsed(map_infos))
			break ;
		line = get_next_line(fd);
	}
	if (!all_elements_parsed(map_infos))
		return (close(fd), print_missing_elements_error(map_infos));
	parse_map_to_queue(fd, &map_infos->queue);
	return (close(fd), SUCCESS);
}
