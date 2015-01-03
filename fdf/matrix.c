#include "header.h"
#include <math.h>

t_matrix *ft_Rx(double B)
{
	t_matrix *m;

	m = (t_matrix *)ft_memalloc(sizeof(t_matrix));
	m->a = 1;
	m->f = cos(B);
	m->g = -sin(B);
	m->j = sin(B);
	m->k = cos(B);
	m->p = 1;
	return (m);
}

t_matrix *ft_Ry(double B)
{
	t_matrix *m;

	m = (t_matrix *)ft_memalloc(sizeof(t_matrix));
	m->a = cos(B);
	m->c = sin(B);
	m->f = 1;
	m->i = -sin(B);
	m->k = cos(B);
	m->p = 1;
	return (m);
}

t_matrix *ft_Rz(double B)
{
	t_matrix *m;

	m = (t_matrix *)ft_memalloc(sizeof(t_matrix));
	m->a = cos(B);
	m->b = -sin(B);
	m->e = sin(B);
	m->f = cos(B);
	m->k = 1;
	m->p = 1;
	return (m);
}

t_matrix	*ft_trans(double i, double j, double k)
{
	t_matrix	*m;
	
	m  = m_ident();
	m->d = i;
	m->h = j;
	m->l = k;
	return (m);
}


t_matrix *ft_Sc(double x, double y, double z)
{
	t_matrix *m;

	m = (t_matrix *)ft_memalloc(sizeof(t_matrix));
	m->a = x;
	m->f = y;
	m->k = z;
	m->p = 1;
	return (m);
}
