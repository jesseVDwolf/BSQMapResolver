#include "map.h"
#include "ft.h"
#include <stdlib.h>
#include <unistd.h>

int			find_max_size(t_bsqmap *map, int row, int col, int size)
{
	int		index;
	int		i;
	int		sum;

	if (map->grid[row][col] != 0)
		return (size - 1);
	else
	{
		sum = 0;
		index = 0;
		while (index < size)
		{
			i = 0;
			while (i < size)
			{
				sum += map->grid[row + index][col + i];
				i++;
			}
			index++;
		}
		if (sum == 0)
		{
			if (size == (map->setting->height - row) || size == (map->setting->width - col))
				return (size);
			else
				return (find_max_size(map, row, col, size + 1));
		}
		else
			return (size - 1);
	}
}

char        **split_rows(t_bsqmap *map)
{
    char    **rows;
	char	*ptr;
	int		idx;

	ptr = ft_strchr(map->mapstr, '\n') + 1;
    if ((rows = malloc(sizeof(char*) * map->setting->height)) == NULL)
		return (rows);
	idx = 0;
	while (ptr[idx] != '\0')
	{
		if (ptr[idx] == '\n')
		{
			*rows = ft_substr(ptr, (idx - map->setting->width), map->setting->width);
			rows++;
		}
		idx++;
	}
	rows -= map->setting->height;
	return (rows);
}

int			*convert_map_line(char *str, t_bsqmap_setting *settings)
{
	int		*row;
	int		idx;

	idx = 0;
	if ((row = malloc(sizeof(int) * settings->width)) == NULL)
		return (row);
	while (str[idx] != '\0')
	{
		if (str[idx] == settings->empty)
			row[idx] = 0;
		else if (str[idx] == settings->obstacle)
			row[idx] = 1;
		else
		{
			free(row);
			return (row = NULL);
		}
		idx++;
	}
	return (row);
}

int         **build_grid(t_bsqmap *map)
{
    char    **rows;
    int     **grid;
    int     idx;

	if ((grid = malloc(sizeof(int*) * map->setting->height)) == NULL)
		return (grid);
    if ((rows = split_rows(map)) == NULL)
	{
		free(grid);
		return (grid = NULL);
	}
	idx = 0;
	while (idx < map->setting->height)
	{
		grid[idx] = convert_map_line(rows[idx], map->setting);
		if (!grid[idx])
		{
			free(grid);
			return (grid = NULL);
		}
		idx++;
	}
	return (grid);
}

void        resolve_map(t_bsqmap *map)
{
    int		col;
	int		row;

	map->grid = build_grid(map);
	if (map->grid)
	{
		row = 0;
		while (row < map->setting->height)
		{
			col = 0;
			while (col < map->setting->width)
			{
				map->grid[row][col] = find_max_size(map, row, col, 1);
				col++;
			}
			row++;
		}
	}
}

void		print_map_result(t_bsqmap *map)
{
	t_bsqmap_result	*result;
	char			**rows;
	int				i;
	int				j;

	result = get_map_result(map);
	rows = split_rows(map);
	i = 0;
	while (i < map->setting->height)
	{
		j = 0;
		while (j < map->setting->width)
		{
			if ((i >= result->row && i < (result->row + result->size))
					&& (j >= result->col && j < (result->col + result->size)))
				write(1, &(map->setting->filler), 1);
			else
				write(1, (rows[i] + j), 1);
			j++;
		}
		write(1, "\n", 1);
		i++;
	}
	write(1, "\n", 1);
}