/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 14:16:43 by julnolle          #+#    #+#             */
/*   Updated: 2020/02/20 18:49:12 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <mlx.h>
# include <stdio.h> //<====== A ENLEVER
# include "libft.h"
# include "get_next_line.h"

/*
** --------------------------------- Defines ---------------------------------
*/

# define SUCCESS	0
# define FAILURE	-1
# define TRUE		1
# define FALSE		0

# define NB_STATE	4
# define NB_OBJ		5
# define NB_ENV		4

# define P_R		"R"
# define P_A		"A"
# define P_C		"c"
# define P_L		"l"
# define P_SP		"sp"
# define P_PL		"pl"
# define P_SQ		"sq"
# define P_CY		"cy"
# define P_TR		"tr"

# define STR_ENV	"RAcl"

# define SP			0x000001
# define PL			0x000002
# define SQ			0x000004
# define CY			0x000008
# define TR			0x000010

/*
** ----------------------------------- Enum ----------------------------------
*/

enum			e_bool
{
	false,
	true
};

enum			e_state
{
	ENV,
	OBJECT,
	EMPTY,
	ERROR
};

enum			e_obj
{
	SPHERE,
	PLANE,
	SQUARE,
	CYLINDER,
	TRIANGLE
};

/*
** -------------------------------- Structures -------------------------------
*/

typedef struct		s_state_machine
{
	enum e_state	state;
	int				obj;
}					t_stm;

/*
** <============< graphics structures >============>
*/

/*
** mlibx structure
*/

typedef struct		s_mlx
{
	void	*mlx_ptr;
	void	*mlx_win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}					t_mlx;

/*
** image structure <== to be deleted ??
*/

typedef struct		s_image {
	int		test;
}					t_image;

/*
** window structure
*/

typedef struct		s_win
{
	double		w;
	double		h;
	enum e_bool	set;
}					t_win;

/*
** <============< utilitary structures >============>
*/

/*
** vector structure
*/

typedef struct		s_vector3d
{
	double x;
	double y;
	double z;
}					t_vec3;

/*
** color structure
*/

typedef struct		s_color
{
	int r;
	int g;
	int b;
	int t;
}					t_col;

/*
** <===========< environment structures >===========>
*/

/*
** ambiant light structure
*/

typedef struct		s_ambiant_light
{
	double	lum;
	t_col	color;
}					t_ambl;

/*
** light structure
*/

typedef struct		s_light
{
	double			lum;
	t_vec3			pos;
	t_col			color;
	struct s_light	*next;
}					t_light;

/*
** camera structure
*/

typedef struct		s_camera
{
	t_vec3				pos;
	t_vec3				dir;
	int					fov;
	struct s_camera		*next;
}					t_cam;

/*
** <=============< objects structures >=============>
*/

/*
** sphere structure
*/

typedef struct		s_sphere
{
	t_vec3	pos;
	double	dia;
	t_col	color;
}					t_sp;

/*
** plane structure
*/

typedef struct		s_plane
{
	t_vec3	pos;
	t_vec3	dir;
	t_col	color;
}					t_pl;

/*
** plane structure
*/

typedef struct		s_square
{
	t_vec3	pos;
	t_vec3	dir;
	double	h;
	t_col	color;
}					t_sq;

/*
** cylindre structure
*/

typedef struct		s_cylindre
{
	t_vec3	pos;
	t_vec3	dir;
	t_col	color;
	double	dia;
	double	h;
}					t_cy;

/*
** triangle structure
*/

typedef struct		s_triangle
{
	t_vec3	pos1;
	t_vec3	pos2;
	t_vec3	pos3;
	t_col	color;
}					t_tr;

/*
** objects linked list
*/

/*typedef struct		s_object
{
	enum e_obj		type;
	double			z_pos;
	void			*content;
	struct s_object	*next;
}					t_obj;
*/
typedef struct		s_object
{
	enum e_obj		type;
	double			z_pos;
	union
	{
		t_sp		sp;
		t_pl		pl;
		t_sq		sq;
		t_cy		cy;
		t_tr		tr;
	}				u_obj;
	struct s_object	*next;
}					t_obj;

/*
** All environment + objects structure
*/

typedef struct		s_data
{
	t_win	win;
	t_obj	*objlst;
	t_light	*lights;
	t_ambl	al;
	t_cam	*cams;
}					t_data;

/*
** ------------------------------- Environment ------------------------------
*/

typedef	int			(*t_func)(t_data *, char **, t_stm *);
typedef	int			(*t_func2)(char **, t_obj **, t_data *);
typedef	int			(*t_func3)(char **, t_data *);
int					set_res(char **tab, t_data *data);
int					set_light(char **tab, t_data *data);
int					set_al(char **tab, t_data *data);
int					set_cam(char **tab, t_data *data);
int					set_sp(char **tab, t_obj **objlst, t_data *data);
int					set_sq(char **tab, t_obj **objlst, t_data *data);
int					set_pl(char **tab, t_obj **objlst, t_data *data);
int					set_cy(char **tab, t_obj **objlst, t_data *data);
int					set_tr(char **tab, t_obj **objlst, t_data *data);

/*
** --------------------------------- Vectors --------------------------------
*/

float				ft_dot_product(float *u, float *v, int dim);
void				ft_cross_product(float *u, float *v, float *p);
void				ft_add_vec(float *u, float *v, float *p, int dim);
void				ft_sub_vec(float *u, float *v, float *p, int dim);
float				ft_norm_vec(float *u, int dim);
void				ft_normalize(float *vec, int dim);
float				ft_norm_vec2(float *vec, int dim);
float				*ft_get_normalize(float *vec, int dim);
float				*ft_mult_vec3(float *u, float m);

/*
** ---------------------------------- Utils ---------------------------------
*/

int					ft_launch_window(t_data *data);
void				ft_pixel_put(t_mlx *mlx, int x, int y, int color);
int					create_trgb(int t, int r, int g, int b);
double				ft_atof(const char *str);
void				ft_free_tab2(char **tab);

/*
** ---------------------------------- forms ---------------------------------
*/

void				ft_draw_circle(t_mlx *mlx);
void				ft_draw_square(t_mlx *mlx);
void				ft_draw_triangle(t_mlx *mlx);
void				ft_draw_sphere(t_mlx *mlx);
void				ft_draw_hex(t_mlx *mlx);

/*
** ------------------------------- Ray tracing ------------------------------
*/

void				ft_raytracing(t_mlx *mlx, t_data *data);

#endif
