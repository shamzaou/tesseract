/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamzaou <shamzaou@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 19:18:29 by shamzaou          #+#    #+#             */
/*   Updated: 2024/04/28 19:18:29 by shamzaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	validate_arguments(int argc, char **argv)
{
	if (argc != 2)
	{
		ft_printf_fd(2, "Error\nWrong number of arguments\n");
		return (INVALID_ARG);
	}
	if (ft_strlen(argv[1]) < 5 || ft_strncmp(argv[1] + ft_strlen(argv[1]) - 4,
			".cub", 4) != 0)
	{
		ft_printf_fd(2, "Error\nWrong file extension\n");
		return (INVALID_ARG);
	}
	return (SUCCESS);
}

int	parse_and_validate(int argc, char **argv, t_mdata *map_infos,
		t_map *map)
{
	int	ret;

	if (validate_arguments(argc, argv) != SUCCESS)
		return (INVALID_ARG);
	ret = parse_map(argv[1], map_infos);
	if (ret == SUCCESS)
	{
		convert_queue_to_2d_array(map, &map_infos->queue);
		if (!is_valid_map(map))
			return (WRONG_MAP);
	}
	return (ret);
}

int	main(int argc, char **argv)
{
	t_params	params;

	params = (t_params){0};
	if (parse_and_validate(argc, argv, &params.map_infos,
			&params.map) != SUCCESS)
	{
		free_and_cleanup(&params);
		return (1);
	}
	params.mlx = mlx_init();
	params.win = mlx_new_window(params.mlx, WINDOW_WIDTH, WINDOW_HEIGHT,
			"cub3d");
	if (init_images(&params) != SUCCESS)
		return (1);
	init_player(&params);
	init_colors(&params);
	cast_rays(&params);
	mlx_key_hook(params.win, key_hook, &params);
	mlx_hook(params.win, 17, 1L << 17, close_window, &params);
	mlx_loop_hook(params.mlx, update_window, &params);
	mlx_loop(params.mlx);
}
