/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xacoquan <xacoquan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/25 18:16:15 by xacoquan          #+#    #+#             */
/*   Updated: 2014/12/17 17:06:06 by xacoquan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include "libft/includes/libft.h"
# include <mlx.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# define BUFF_SIZE 10000

typedef struct  s_vector
{
//  int     **tab;
    double  x;
    double  y;
    double  z;
    double  p;
    int     newx;
    int     newy;
    int     color;

}               t_vector;

typedef struct  s_matrix
{
    double a;
    double b;
    double c;
    double d;
    double e;
    double f;
    double g;
    double h;
    double i;
    double j;
    double k;
    double l;
    double m;
    double n;
    double o;
    double p;
}              t_matrix;

typedef struct s_env
{
	void *mlx;
	void *win;
    t_vector ***tab;
    int     col;
    int     line;
    int color;
    t_matrix    *mt;
    t_matrix    *sc;
    t_matrix    *rx;
    t_matrix    *ry;
    t_matrix    *rz;

}              t_env;

void		ft_get_data(int argc, char **argv, t_env *data);
void		ft_data_size(char *file, t_env *data);
void		ft_put_data(char *str, t_env *data);
int			get_next_line(int fd, char **line);
t_matrix    *m_ident();
t_matrix *ft_Rx(double B);
t_matrix *ft_Ry(double B);
t_matrix *ft_Rz(double B);
t_matrix *ft_trans(double i, double j, double k);
t_matrix *ft_Sc(double x, double y, double z);
t_matrix    *mult_matrix(t_matrix *q, t_matrix *w);
 t_vector *vector_matrix(t_matrix *v, t_vector *w);
#endif
