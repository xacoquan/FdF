/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xacoquan <xacoquan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/14 12:33:23 by xacoquan          #+#    #+#             */
/*   Updated: 2014/12/15 17:51:35 by xacoquan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int		empty(char **line, char *ret)
{
	*line = ft_strdup(ret);
//	free(ret);
	ret = NULL;
	if ((*line)[0] == '\0')
		return (0);
	return (1);
}

void	mapping(char *buff, char **fdp, int index)
{
	char *tmp;

	buff[index] = '\0';
	tmp = *fdp;
	*fdp = ft_strjoin(*fdp, buff);
//	printf("%s", tmp);
	free(tmp);
}

int		get_next_line(int const fd, char **line)
{
	char    buff[BUFF_SIZE + 1];
	int     index;
	static char *ret = NULL;
	char    *tmp1;
	char	*tmp2;

	if (fd == -1 || BUFF_SIZE <= 0)
		return (-1);
	if (!ret)
		ret = ft_strnew(0);
	index = 0;
	while ((ft_strchr(ret, '\n') == NULL) && (index = read(fd, buff, BUFF_SIZE)) > 0)
		mapping(buff, &ret, index);
	if (index == -1)
		return (-1);
	else if (index == 0 && ft_strchr(ret, '\n') == NULL)
		return (empty(line, ret));
	tmp1 = ft_strchr(ret, '\n') + 1;
	*line = ft_strsub(ret, 0, (size_t)(tmp1 - 1 - ret));
	tmp2 = ret;
	ret = ft_strdup(tmp1);
//	free(tmp2);
	return (1);
}

/*int		main(int ac, char **av)
{
	int fd;
	char *test;
	int		i;

	i = 1;
	if (av[i])
		fd = open(av[i], O_RDONLY);
	else
		fd = 0;
	if (fd < 0)
	{
		ft_putendl("fichier pas trouver");
		exit(0);
	}
	while (get_next_line(fd, &test) > 0)
	{
		printf("%s\n", test);
		free(test);
	}
//	printf("%s\n", test);
	free(test);
	return (ac);
}
*/
