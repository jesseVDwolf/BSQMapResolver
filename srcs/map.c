#include "map.h"
#include "ft.h"
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

#include <stdio.h>

char    			*read_file(int fd)
{
    char *map;
    int size;

    map = malloc(sizeof(char) * BUFFSIZE);
    if (!map)
        return (map);
    size = read(fd, map, BUFFSIZE);
    if (size == -1 || close(fd) == -1)
    {
		free(map);
		return (map = NULL);
	}
    return (map);
}

int         is_valid_map_setting(const char *map)
{
    int     idx;
    char    *p;

    idx = 1;
    p = ft_strchr(map, '\n');
    while ((p - idx) != (map - 1))
    {
        if ((idx >= 1) && (idx <= 3))
        {
            if (!ft_isprint(*(p - idx)))
            {
                return (0);
            }
        }
        else
        {
            if (!ft_isdigit(*(p - idx)))
            {
                return (0);
            }
        }
        idx++;
    }
    return (1);
}

int         	is_valid_map(const char *map)
{
    /*
    * 1. All lines must have the same length
    * 2. There's at least one line of at least one box
    * 3. At each end of line, there's a line break
    * 4. The characters on the map can only be those introduced in the first line
    */
    int 				idx;
    int 				linecount;
    char 				*p;
    t_bsqmap_setting	*setting;

    if (!is_valid_map_setting(map))
        return (0);
    idx = 0;
    linecount = 0;
    p = ft_strchr(map, '\n') + 1;
    setting = get_map_setting(map);
    while (p[idx] != '\0')
    {
        // the characters on the map can only be those introcuded
        // in the first line. Also, map cannot contain filler 
        // characters yet.
        if ((p[idx] != setting->empty) && (p[idx] != setting->obstacle) && (p[idx] != '\n'))
            return (0);
        else if (p[idx] == '\n')
        {
            // all lines must be the same lenght which is 
            // based on the dimension provided in the first line.
            if (((idx - linecount) % setting->width) != 0)
                return (0);
            linecount++;
        }
        idx++;
    }
    // index must be bigger than dim since at least one 
    // line has to be present which is dim amount of obstacle
    // or empty characters plus an end of line character.
    return ((idx > setting->width) && (linecount == setting->height));
}

t_bsqmap_result		*get_map_result(t_bsqmap *map)
{
	t_bsqmap_result *result;
	int				i;
	int				j;

	if ((result = malloc(sizeof(t_bsqmap_result))) == NULL)
		return (result);
	i = 0;
	while (i < map->setting->height)
	{
		j = 0;
		while (j < map->setting->width)
		{
			if (map->grid[i][j] > result->size)
			{
				result->size = map->grid[i][j];
				result->row = i;
				result->col = j;
			}
			j++;
		}
		i++;
	}
	return (result);
}

int         		get_map_height(const char *map)
{
    int		idx;
    int		height;
    char	*nbr;

    idx = 0;
    while (map[idx] != '\n')
        idx++;
    nbr = ft_substr(map, 0, (idx - 3));
    height = ft_atoi(nbr);
    return (height);
}

int					get_map_width(const char *map)
{
	int		idx;
	int		width;
	char	*p;

	idx = 0;
	width = 0;
	p = ft_strchr(map, '\n') + 1;
	while (p[idx++] != '\n')
		width++;
	return (width);
}

t_bsqmap_setting	*get_map_setting(const char *map)
{
    t_bsqmap_setting *setting;

    setting = malloc(sizeof(t_bsqmap_setting));
    if (!setting)
        return (setting);
    setting->width = get_map_width(map);
	setting->height = get_map_height(map);
    setting->empty = *(ft_strchr(map, '\n') - 3);
    setting->obstacle = *(ft_strchr(map, '\n') - 2);
    setting->filler = *(ft_strchr(map, '\n') - 1);
    return (setting);
}

t_bsqmap    		*init_map(int fd)
{
    t_bsqmap *map;

    map = malloc(sizeof(t_bsqmap));
    if (!map)
        return (map);
    map->mapstr = read_file(fd);
    if (!(map->mapstr) || !is_valid_map(map->mapstr))
    {
		free(map);
		return (map = NULL);
	}
    map->setting = get_map_setting(map->mapstr);
    map->grid = NULL;
    return (map);
}

t_bsqmap    		**load_from_args(int fcount, char **fnames)
{
    t_bsqmap	**maps;
    int 		index;
    int 		fd;

    index = 0;
    maps = malloc(sizeof(t_bsqmap*) * fcount);
    if (!maps)
        return (maps);
    while (index < fcount)
    {
        fd = open(fnames[index], O_RDONLY);
		maps[index] = (fd == -1) ? NULL : init_map(fd);
        index++;
    }
    return (maps);
}