#include "header.h"

 t_matrix	*mult_matrix(t_matrix *q, t_matrix *w)
 {
 	t_matrix *m;
 	m = (t_matrix *)malloc(sizeof(t_matrix));
 	m->a = q->a * w->a + q->b * w->e + q->c * w->i + q->d * w->m;
 	m->b = q->a * w->b + q->b * w->f + q->c * w->j + q->d * w->n;
 	m->c = q->a * w->c + q->b * w->g + q->c * w->k + q->d * w->o;
 	m->d = q->a * w->d + q->b * w->h + q->c * w->l + q->d * w->p;
 	m->e = q->e * w->a + q->f * w->e + q->g * w->i + q->h * w->m;
 	m->f = q->e * w->b + q->f * w->f + q->g * w->j + q->h * w->n;
 	m->g = q->e * w->c + q->f * w->g + q->g * w->k + q->h * w->o;
 	m->h = q->e * w->d + q->f * w->h + q->g * w->l + q->h * w->p;
 	m->i = q->i * w->a + q->j * w->e + q->k * w->i + q->l * w->m;
 	m->j = q->i * w->b + q->j * w->f + q->k * w->j + q->l * w->n;
 	m->k = q->i * w->c + q->j * w->g + q->k * w->k + q->l * w->o;
 	m->l = q->i * w->d + q->j * w->h + q->k * w->l + q->l * w->p;
 	m->m = q->m * w->a + q->n * w->e + q->o * w->i + q->p * w->m;
 	m->n = q->m * w->b + q->n * w->f + q->o * w->j + q->p * w->n;
 	m->o = q->m * w->c + q->n * w->g + q->o * w->k + q->p * w->o;
	m->p = q->m * w->d + q->n * w->h + q->o * w->l + q->p * w->p;
 	return (m);
 }

t_matrix    *m_ident()
{
    t_matrix    *m;

    m = (t_matrix *)ft_memalloc(sizeof(t_matrix));
    m->a = 1;
    m->f = 1;
    m->k = 1;
    m->p = 1;
    return (m);
}

t_vector        *vector_matrix(t_matrix *m, t_vector *o)
{
    t_vector    *v;
	
    v = (t_vector *)malloc(sizeof(t_vector));
    v->x = m->a * o->x + m->b * o->y + m->c * o->z + m->d * o->p;
    v->y = m->e * o->x + m->f * o->y + m->g * o->z + m->h * o->p;
    v->z = m->i * o->x + m->j * o->y + m->k * o->z + m->l * o->p;
    v->p = m->m * o->x + m->n * o->y + m->o * o->z + m->p * o->p;
    v->newx = 0;
    v->newy = 0;
    v->color = o->color;
	printf("%f,%f,%f,%f \n" , m->e,m->f ,m->g, m->h);
	//printf("This :\n    %f, %f, %f, %f\nBecame this :\n    %f, %f, %f, %f\n\n", o->x, o->y, o->z, o->p, v->x, v->y  , v->z, v->p);
    //free(o);
    return (v);
}
