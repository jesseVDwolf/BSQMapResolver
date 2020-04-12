#include "map.h"
#include "grid.h"
#include <stdlib.h>
#include <unistd.h>

int	main(int argc, char **argv)
{
	t_bsqmap	**maps;
    int			idx;
    int			nmaps;

    if (argc == 1)
    {
        maps = malloc(sizeof(t_bsqmap*));
        *maps = init_map(0);
    }
    else
        maps = load_from_args(argc - 1, argv + 1);
    idx = 0;
    nmaps = (argc == 1) ? argc : (argc - 1);
    while (idx < nmaps)
    {
        if (!maps[idx])
            write(2, "map error\n", 10);
        else
        {
			resolve_map(maps[idx]);
			(maps[idx]->grid) ? print_map_result(maps[idx]) : write(2, "map error\n", 10);
        }
		idx++;
	}
	return (0);
}
