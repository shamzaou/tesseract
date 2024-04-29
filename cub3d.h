/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alabdull <@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 19:19:55 by shamzaou          #+#    #+#             */
/*   Updated: 2024/04/29 18:23:28 by alabdull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <errno.h>
# include <sys/errno.h>
# include <fcntl.h>
# include <limits.h>
# include <sys/stat.h>
# include <sys/types.h>

# include "libft/libft.h"
# include "mlx/mlx.h"

# define WINDOW_WIDTH 800
# define WINDOW_HEIGHT 800
# define RESOLUTION 800
# define TILE_SIZE 64
# define TEXTURE_SIZE 64
# define MOVE_SPEED 40
# define ROTATE_SPEED 0.5
# define HORIZONTAL 0
# define VERTICAL 1

typedef enum e_error
{
	SUCCESS,
	INVALID_ARG,
	WRONG_INPUT,
	WRONG_MAP,
	MALLOC_FAIL,
	OPEN_ERR,
	MLX_FAIL,
	IMG_FAIL,
	WRONG_TEXTURE,
	WRITE_FAIL
}						t_error;

typedef struct s_point
{
	int					x;
	int					y;
}						t_point;

typedef struct s_fpoint
{
	float				x;
	float				y;
}						t_fpoint;

typedef struct s_color
{
	int					red;
	int					green;
	int					blue;
}						t_color;

typedef struct s_queue_node
{
	char				*val;
	struct s_queue_node	*next;
}						t_queue_node;

typedef struct s_queue
{
	t_queue_node		*front;
	t_queue_node		*rear;
}						t_queue;

typedef struct s_map_info
{
	char				*no_path;
	char				*so_path;
	char				*we_path;
	char				*ea_path;

	t_color				floor_color;
	t_color				ceiling_color;

	t_queue				queue;

	int					no_path_parsed;
	int					so_path_parsed;
	int					we_path_parsed;
	int					ea_path_parsed;
	int					floor_color_parsed;
	int					ceiling_color_parsed;

}						t_mdata;

typedef struct s_map
{
	int					cols;
	int					rows;
	char				**map_data;
}						t_map;

typedef struct s_gdata
{
	void				*img;
	char				*addr;
	int					bits_per_pixel;
	int					bpp;
	int					line_length;
	int					endian;
	int					width;
	int					height;
}						t_gdata;

typedef struct s_player
{
	double				x;
	double				y;
	double				dx;
	double				dy;
	double				direction;
	double				fov;
}						t_player;

typedef struct s_ray
{
	double				x;
	double				y;
	double				direction;
	double				length;
	int					hit;
}						t_ray;

typedef struct s_wall
{
	double				wall_height;
	char				*wall_texture;
	t_gdata				*texture_img;
	int					texture_x;
	int					texture_y;
	int					wall_y;
}						t_wall;

typedef struct s_params
{
	void				*mlx;
	void				*win;
	t_gdata				window_img;

	t_map				map;
	t_mdata			map_infos;

	t_player			player;
	t_ray				ray;

	t_gdata				north_texture;
	t_gdata				south_texture;
	t_gdata				west_texture;
	t_gdata				east_texture;

	int					floor_color;
	int					ceiling_color;

	t_wall				wall;

}						t_params;

/* >>>>>>>>> parsing.c <<<<<<<< */
int						parse_map(char *file_name, t_mdata *map_infos);

/* >>>>>>>>> parsing_validation.c <<<<<<<< */
int						validate_colors(t_color *color, char **colors);
int						is_valid_texture_path(char *path);

/* >>>>>>>>> map_validation.c <<<<<<<< */
int						is_valid_map(t_map *map);

/* >>>>>>>>> init.c <<<<<<<< */
void					init_player(t_params *params);
void					init_params(t_params *params);
void					init_colors(t_params *params);

/* >>>>>>>>> parsing_helpers.c <<<<<<<< */
int						startswith(char **array, char *str);
int						array_size(char **array);
int						is_empty_line(char *line);
int						open_map_file(char *file_name);
int						is_numeric(char *str);

/* >>>>>>>>> map.c <<<<<<<< */
void					convert_queue_to_2d_array(t_map *map, t_queue *queue);

/* >>>>>>>>> malx_draw.c <<<<<<<< */
t_point					init_point(int x, int y);
int						mlx_pixel_put_img(t_params *params, int x, int y,
							int color);
void					my_mlx_pixel_put(t_gdata *data, int x, int y, int color);

/* >>>>>>>>> raycasting.c <<<<<<<< */
void					cast_rays(t_params *params);

/* >>>>>>>>> queue.c <<<<<<<< */
void					init_queue(t_queue *q);
void					enqueue(t_queue *q, void *val);
void					*dequeue(t_queue *q);
char					*queue_to_str(t_queue *q);
void					free_queue(t_queue *q);

/* >>>>>>>>> line.c <<<<<<<< */
void					draw_line(t_params *params, t_point p1, t_point p2,
							int color);
void					draw_line_img(t_params *params, t_point p1, t_point p2,
							int color);

/* >>>>>>>>> player_movements.c <<<<<<<< */
void					look_left(t_params *params);
void					look_right(t_params *params);
void					move_up(t_params *params);
void					move_down(t_params *params);
void					move_left(t_params *params);
void					move_right(t_params *params);

/* >>>>>>>>> player_actions.c <<<<<<<< */
void					normalize_direction(double *direction);
void					look_left(t_params *params);
void					look_right(t_params *params);

/* >>>>>>>>> init_images.c <<<<<<<< */
int						init_images(t_params *params);

/* >>>>>>>>> rendering.c <<<<<<<< */
void					get_wall_texture(t_params *params, t_ray *ray,
							t_wall *wall);
void					render_wall_texture(t_params *params, t_wall *wall,
							int column);
void					render_ground_and_ceiling(t_params *params,
							t_wall *wall, int column);

/* >>>>>>>>> hook.c <<<<<<<< */
int						key_hook(int keycode, t_params *params);
int						update_window(t_params *params);
int						close_window(t_params *params);

/* >>>>>>>>> ray_intersections.c <<<<<<<< */
double					calculate_distance(double x1, double y1, double x2,
							double y2);
t_fpoint				horizontal_ray_intersection(t_params *params,
							double angle);
t_fpoint				vertical_ray_intersection(t_params *params,
							double angle);


/* >>>>>>>>> parse_line.c <<<<<<<< */
int						handle_texture_line(t_mdata *map_infos,
							char ***array, int *parsed_flag);

int						handle_color_line(t_mdata *map_infos, char ***array,
							int *parsed_flag);

/* >>>>>>>>> map_error_handling.c <<<<<<<< */
int						handle_invalid_line(char ***array, char *map_line);
int						print_missing_elements_error(t_mdata *map_infos);

/* >>>>>>>>> free.c <<<<<<<< */
void					ft_free(void **ptr);
void					free_split_array(char **array);
void					free_and_cleanup(t_params *params);
void					free_2d_array(char ***map);
void					free_map_infos(t_mdata *map_infos);

#endif /* CUB3D_H */