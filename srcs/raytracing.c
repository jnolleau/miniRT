/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 14:18:43 by julnolle          #+#    #+#             */
/*   Updated: 2020/02/11 14:24:41 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "libft.h"


/*	ALGO :
** Place the eye and the frame as desired (1)
** For each pixel on the screen
**     Determine the square on the grid corresponding to this pixel (2)
**     Determine the color seen through that square (3)
**     Paint the pixel with that color (4)
*/

int		ft_intersec(float *dir, t_sp *sp)
{
	(void)sp;
	float origin[3] = {0.0, 0.0, 0.0};
	float center[3] = {sp->pos.x, sp->pos.y, sp->pos.z};
	float oc[3];
	float r = sp->dia;
	float a;
	float b;
	float c;
	float delta;
	double t1;
	double t2;
	ft_sub_vec(origin, center, oc, 3);
	a = 1;
	b = 2.0 * ft_dot_product(dir, oc, 3);
	c = ft_norm_vec2(oc, 3) - ((r/2) * (r/2));
	delta = b * b - 4 * a * c;
	if (delta < 0)
		return (0);
	t1 = (-b - sqrt(delta)) / (2 * a);
	t2 = (-b + sqrt(delta)) / (2 * a);
	// printf("t1 :%f | t2 :%f\n", t1, t2);
	if (t2 > 0 || delta == 0)
		return (1);
	return (0);
}

void	ft_raytracing(t_data *data, t_win *win)
{
	float	dir[3];
	t_sp	sp;
	t_sp	sp2;
	t_light	li;
	float	fov;
	float	i;
	float	j;
	float 	height;
	float 	width;

	sp.pos.x = 6.0;
	sp.pos.y = -2.0;
	sp.pos.z = -25.0;
	sp.dia = 8.0;	

	sp2.pos.x = -5.0;
	sp2.pos.y = 1000.0;
	sp2.pos.z = -200.0;
	sp2.dia = 2000;

	li.lum = 0.9;
	li.pos.x = 15;
	li.pos.y = 60;
	li.pos.z = -40;

	fov = 60 * M_PI / 180;
	i = 0;
	while (i < win->w - 1)
	{
		j = 0;
		while (j < win->h - 1)
		{
			dir[0] = i - win->w / 2;
			dir[1] = j - win->h / 2;
			dir[2] = -win->w / (2.0 * tan(fov / 2.0));
			ft_normalize(dir, 3);

			if (ft_intersec(dir, &sp2) == 1)
				ft_pixel_put(data, i, j, create_trgb((j/win->h)*255, 69, 0, 0));
			else if (ft_intersec(dir, &sp) == 1)
				ft_pixel_put(data, i, j, create_trgb((j/win->h)*255, 69, 255, 0));
			else
				ft_pixel_put(data, i, j, create_trgb((j/win->h)*255, 255, 255, 0));
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(data, data->mlx_win, data->img, 0, 0);
}

/*void	ft_raytracing(t_data *data, t_win *win)
{
int	cam_x = 0;
	double	cam_y = 0;
	double	cam_z = 20;	
	double	cam_or_x = 0;
	double	cam_or_y = 0;
	double	cam_or_z = 1;
	// int	fov = 0;
	// double d[] = [0, 0, 1];
	// double O[] = [0, 0, 0];
	double	xo = 0;
	double	yo = 0;	
	int	x = 0;
	int	y = 0;
	double	i;
	double	j;

	i = 0;
	while (i < win->w)
	{
		j = 0;
		while (j < win->h)
		{
			xo = (i + 0.5) / 2;
			yo = (j + 0.5) / 2;
			x = xo * 2 - 1;
			y = yo * 2 - 1;

			ft_pixel_put(data, x, y, 0xFFFF00);
			j++;
		}
		i++;
	}
	ft_putnbr(i * j);
	mlx_put_image_to_window(data, data->mlx_win, data->img, 0, 0);


}
*/