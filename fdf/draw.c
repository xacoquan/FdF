/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xacoquan <xacoquan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/09 15:28:09 by xacoquan          #+#    #+#             */
/*   Updated: 2015/01/03 09:52:29 by xacoquan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <math.h>
#include <stdio.h>

void	ft_draw_h(double derr, t_env *data, t_vector *p1, t_vector *p2)
{
	int		x;
	int		y;
	double	err;
	int		in;

	x = p1->newx;
	y = p1->newy;
	err = 0;
	while (x < p2->newx)
	{
		mlx_pixel_put(data->mlx, data->win, x, y, 0x00ff00);
		err += derr;
		if (err > 0.5)
		{
			y += (p1->newy < p2->newy) ? 1 : -1;
			err -= 1.0;
		}
		x++;
	}
}

void	ft_draw_l(double derr, t_env *data, t_vector *p1, t_vector *p2)
{
	int		x;
	int		y;
	double	err;
	int		in;

	x = p1->newx;
	y = p1->newy;
	err = 0;
	while (y < p2->newy)
	{
		mlx_pixel_put(data->mlx, data->win, x, y, 0xff0000);
		err += derr;
		if (err > 0.5)
		{
			x += (p1->newx < p2->newx) ? 1 : -1;
			err -= 1.0;
		}
		y++;
	}
}

void	draw_line(t_vector *p1, t_vector *p2, t_env *data)
{
	double	dx;
	double	dy;

	dx = abs(p2->newx - p1->newx);
	dy = abs(p2->newy - p1->newy);
	if (dx > dy && (p1->newx > p2->newx))
		draw_line(p2, p1, data);
	else if (dx > dy)
		ft_draw_h(dy / dx, data, p1, p2);
	else if (p1->newy > p2->newy)
		draw_line(p2, p1, data);
	else
		ft_draw_l(dx / dy, data, p1, p2);
}

void ft_apply_mtomap(t_matrix *m, t_env *e)
{
	unsigned int x;
	unsigned int y;

 
	y = 0;
	while ((e->tab)[y])
	{
		x = 0;
		while ((e->tab)[y][x])
		{
			(e->tab)[y][x] = vector_matrix(m, (e->tab)[y][x]);
			x++;
		}
		y++;
	}
}

void	draw(t_env *e)
{
	unsigned int	x;
	unsigned int	y;
	t_matrix		*m;

	y = 0;
	m = mult_matrix(m_ident(), e->rx);
	m = mult_matrix(m, e->sc);
	m = mult_matrix(m, e->rz);
	m = mult_matrix(m, e->ry);
	while ((e->tab)[y])
	{
		x = 0;
		while ((e->tab)[y][x])
		{
			(e->tab)[y][x] = vector_matrix(m, (e->tab)[y][x]);
			(e->tab)[y][x] = vector_matrix(e->mt, (e->tab)[y][x]);
			(e->tab)[y][x]->newx = (e->tab)[y][x]->x;
			(e->tab)[y][x]->newy = (e->tab)[y][x]->y;
			//if ((e->tab)[y][x])
			//mlx_pixel_put(e->mlx, e->win, (e->tab)[y][x]->x, (e->tab)[y][x]->y, (e->tab)[y][x]->color);
			(e->tab)[y][x]->newx = (int)((sqrt(2) / 2) * \
				((e->tab)[y][x]->x - (e->tab)[y][x]->y) + 2000 / 2);
			(e->tab)[y][x]->newy = (int)(((sqrt(2) * -1) / 2) * sin(1) * \
				((e->tab)[y][x]->x + (e->tab)[y][x]->y) + (cos(1) * (-1 * ((e->tab)[y][x]->z)) + (700 / 2)));
			mlx_pixel_put(e->mlx, e->win, (e->tab)[y][x]->newx, (e->tab)[y][x]->newy, (e->tab)[y][x]->color);
			if (y > 0)
						draw_line(e->tab[y - 1][x], e->tab[y][x], e);
			if (x > 0)
			draw_line(e->tab[y][x - 1], e->tab[y][x], e);
			x++;
		}
		y++;
	}
}

int		expose_hook(t_env *e)
{
	draw(e);
	return (0);
} 

void	keys1(int keycode, t_env *e)
{

}

int 	key_hook(int keycode, t_env *e)
{
	free(e->mt);
	free(e->sc);
	free(e->rx);
	free(e->ry);
	free(e->rz);
	e->mt = m_ident();
	e->sc = m_ident();
	e->rx = m_ident();
	e->ry = m_ident();
	e->rz = m_ident();
	if (keycode == 65307)
		exit (0);
	if (keycode == 45) // '-'
	{
		free(e->sc);
		e->sc = ft_Sc(9.0 / 10.0, 9.0 / 10.0, 9.0 / 10.0);
		mlx_clear_window(e->mlx, e->win);
       		draw(e);
	}
	if (keycode == 61) // '+'
	{
		free(e->sc);
		e->sc = ft_Sc(10.0 / 9.0, 10.0 / 9.0, 10.0 / 9.0);
		mlx_clear_window(e->mlx, e->win);
		draw(e);
	}
	if (keycode == 114) // 'r'
	{
		free(e->rx);
		e->rx = ft_Rx(.5);
		mlx_clear_window(e->mlx, e->win);
		draw(e);
	}
	if (keycode == 116) // 't'
	{
		free(e->rx);
		e->rx = ft_Rx(-.5);
		mlx_clear_window(e->mlx, e->win);
		draw(e);
	}
	if (keycode == 102) // 'f'
	{
		free(e->ry);
		e->ry = ft_Ry(.5);
		mlx_clear_window(e->mlx, e->win);
		draw(e);
	}
	if (keycode == 103) // 'g'
	{
		free(e->ry);
		e->ry = ft_Ry(-.5);
		mlx_clear_window(e->mlx, e->win);
		draw(e);
	}
	if (keycode == 118) // 'v'
	{
		free(e->rz);
		e->rz = ft_Rz(.5);
		mlx_clear_window(e->mlx, e->win);
		draw(e);
	}
	if (keycode == 98) // 'b'
	{
		free(e->rz);
		e->rz = ft_Rz(-.5);
		mlx_clear_window(e->mlx, e->win);
		draw(e);
	}
	if (keycode == 65362) // 'haut'
	{
		free(e->mt);
		e->mt = ft_trans(10.0, 10.0, 10.0);
		mlx_clear_window(e->mlx, e->win);
		draw(e);
	}
	if (keycode == 65364) // 'bas'
	{
		free(e->mt);
		e->mt = ft_trans(-10.0, -10.0, -10.0);
		mlx_clear_window(e->mlx, e->win);
		draw(e);
	}
	if (keycode == 65361) // 'gauche'
	{
		free(e->mt);
		e->mt = ft_trans(10.0, 10.0, 10.0);
		mlx_clear_window(e->mlx, e->win);
		draw(e);
	}
	if (keycode == 65363) // 'droite'
	{
		free(e->mt);
		e->mt = ft_trans(10.0, 10.0, 10.0);
		mlx_clear_window(e->mlx, e->win);
		draw(e);
	}
	return (0);	
}

void		ft_init(t_env *e)
{
	e->mt = ft_trans(((double)(2 / 2)), ((double)(2 / 2)), (double)2);
	e->sc = ft_Sc(15.0, 15.0, 15.0);
	e->rx = ft_Rx(1.0);
	e->ry = ft_Ry(0);
	e->rz = ft_Rz(0.5);
}

int main(int ac, char **av)
{
	//printf("M :\n%f %f %f %f\n%f %f %f %f\n%f %f %f %f\n%f %f %f %f\n", m->a, m->b, m->c, m->d, m->e, m->f, m->g, m->h, m->i, m->j, m->k, m->l, m->m, m->n, m->o, m->p);
	t_env *e;

	e = (t_env *)ft_memalloc(sizeof(t_env));
	e->mlx = mlx_init();
	e->win = mlx_new_window(e->mlx, 2000, 2000, "42");
	ft_get_data(ac, av, e);
	// ft_apply_mtomap(ft_Sc(20, 20, 20), e);
	// ft_apply_mtomap(ft_Rx(4), e);
	// ft_apply_mtomap(ft_Ry(3), e);
	// ft_apply_mtomap(ft_Rz(3), e);
	// ft_apply_mtomap(ft_trans(200, 200, 200), e);
	ft_init(e);
	mlx_hook(e->win, 2, 3, key_hook, e);
	mlx_expose_hook(e->win, expose_hook, e);
	mlx_loop(e->mlx);
//	draw(e.mlx, e.win);

return (0);		
}
