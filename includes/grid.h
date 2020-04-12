#ifndef FT_GRID_H

#define FT_GRID_H

#include "map.h"

int			find_max_size(t_bsqmap *map, int row, int col, int size);

char        **split_rows(t_bsqmap *map);

int			*convert_map_line(char *str, t_bsqmap_setting *settings);

int         **build_grid(t_bsqmap *map);

void        resolve_map(t_bsqmap *map);

void		print_map_result(t_bsqmap *map);

#endif

