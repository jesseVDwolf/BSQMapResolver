#ifndef FT_MAP_H

#define FT_MAP_H

#define BUFFSIZE 8000000

typedef  struct         s_map_setting
{
    int                 height;
	int					width;
    char                empty;
    char                filler;
    char                obstacle;
}                       t_bsqmap_setting;

typedef struct          s_map
{
    t_bsqmap_setting    *setting;
    const char          *mapstr;
    int                 **grid;
}                       t_bsqmap;

typedef	struct			s_bsqmap_result
{
	int					size;
	int					col;
	int					row;
}						t_bsqmap_result;

t_bsqmap            	**load_from_args(int fcount, char **fnames);

t_bsqmap    			*init_map(int fd);

t_bsqmap_setting		*get_map_setting(const char *map);

char    				*read_file(int fd);

t_bsqmap_result			*get_map_result(t_bsqmap *map);

int         			get_map_height(const char *map);

int						get_map_width(const char *map);

int                 	is_valid_map_setting(const char *map);

int                 	is_valid_map(const char *map);

#endif