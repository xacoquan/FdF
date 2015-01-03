/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xacoquan <xacoquan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/25 18:14:33 by xacoquan          #+#    #+#             */
/*   Updated: 2014/12/28 04:59:18 by xacoquan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "header.h"

void	ft_get_data(int argc, char **argv, t_env *data)
{
	if (argc != 2)
	{
		ft_putstr("usage: ./fdf [data_file]\n");
		exit(0);
	}
	ft_data_size(argv[1], data);
	ft_put_data(argv[1], data);
}

int     ft_column_cnt(char *str)
{
    int ret;
    int i;
    int j;

    ret = 0;
    i = 0;
    while (str[i])
    {
        j = 0;
        while (ft_isdigit(str[i + j]))
            j++;
        if (j)
            ret++;
        i += j;
        while (str[i] == ' ' &&  !ft_isdigit(str[i]))
            i++;
        if (str[i] != ' ' && !ft_isdigit(str[i]) && str[i] != 0)
        {
            ft_putstr("error connard");
            exit (0);
        }
    }
    return (ret);
}

void	ft_data_size(char *file, t_env *data)
{
	write(1, "78\n", 3);
	int		fd;
 	char	*line1;
	write(1, "71\n", 3);

	data->line = 0;
	write(1, "76\n", 3);
	if ((fd = open(file, O_RDONLY)) == -1)
	{
		ft_putstr("usage: ./fdf [data_file]\n");
		exit(0);
	}
	while (get_next_line(fd, &line1) > 0)
	{
		write(1, "82\n", 3);
		data->col = ft_column_cnt(line1);
//		free(line);
		data->line++;
	}
	close(fd);
}

int		take_z(char *str, int n)
{
	int		ret;
	int		i;
	int		j;

	i = 0;
	ret = 0;
	while (str[i])
	{
		if (ret == n)
			return (ft_atoi(str + i));
		while (!ft_isdigit(str[i]) && str[i])
			i++;
		while (ft_isdigit(str[i]))
			i++;
		ret++;
	}
	return (0);
}



void	ft_put_data(char *file, t_env *data)
{
	int		line;
	int		col;
	char	*str;
	int		fd;

	if ((fd = open(file, O_RDONLY)) == -1)
	{
		ft_putstr("usage: ./fdf [data_file]\n");
		exit(0);
	}
//	printf("%s", str);
//	chartab = ft_strsplit(str, ' ');
//	i = ft_tablen(chartab);
	data->tab = (t_vector***)malloc((data->line + 1) * (sizeof(t_vector**)));
	line = 0;
	while (line < data->line)
	{
		data->tab[line] = (t_vector**)malloc(sizeof(t_vector *) * (data->col + 1));
		get_next_line(fd, &str);
		col = 0;
		while (col < data->col)
		{
//traiter str
			data->tab[line][col] = (t_vector*)malloc(sizeof(t_vector));
			data->tab[line][col]->x = line;
			data->tab[line][col]->y = col;
			data->tab[line][col]->z = take_z(str, col);
			data->tab[line][col]->p = 1;
			data->tab[line][col]->color = 0x00FF00;
			col++;
			//write(1, "fdp\n", 4);
		}
		//free(str);
		data->tab[line][col] = NULL;
		line++;
	}
	data->tab[line] = NULL;
	close(fd);
}
