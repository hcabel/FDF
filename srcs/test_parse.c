




static t_vector	*initi(t_map *map, t_point **start, t_vector *v, char **stock, t_info *info)
{
	t_point		*tmp;
	t_vector	*v2;
	int			i;

	v2 = cp_vector(*v, info);
	free(v);
	v2->z = ft_atoi(stock[(int)v2->x]);
	if (ft_strchr(stock[(int)v2->x], ','))
	{
		i = 1;
		while (stock[(int)v2->x][i - 1] != ',')
			i++;
		v2->colour = hexa2int(stock[(int)v2->x] + i, info);
		v2->colour_is_define = 1;
	}
	if (map->small == NULL || v2->z < map->small->z)
		map->small = v2;
	else if (map->big == NULL || v2->z > map->big->z)
		map->big = v2;
	tmp = newlink(cp_vector(*v2, info), info);
	if (*start == NULL)
		*start = tmp;
	if (tmp->v->x > 0)
		getref(*start, tmp->v->x - 1, tmp->v->y)->n1 = tmp;
	if (tmp->v->y > 0)
		getref(*start, tmp->v->x, tmp->v->y - 1)->n2 = tmp;
	v2->colour_is_define = 0;
	v2->x++;
	return (v2);
}

//static t_vector	*initi2()

t_point			*parsing(t_map *map, int fd, t_info *info)
{
	t_point		*start;
	t_vector	*v;
	char		*line;
	char		**stock;
	int			ret;

	start = NULL;
	v = init_vector(0, 0, 0, info);
	while ((ret = get_next_line(fd, &line)) == 1)
	{
		check_file(line, map, info);
		v->x = 0;
		stock = ft_strsplit(line, ' ');
		while (stock[(int)v->x])
			v = initi(map, &start, v, stock, info);
		v->y++;
		free(stock);
		free(line);
	}
	if (ret == -1)
		finish(info, "Error file !");
	map->size_x = v->x - 1;
	map->size_y = v->y - 1;
	close(fd);
	free(v);
	return (start);
}