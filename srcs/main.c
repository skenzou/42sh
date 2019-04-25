#include "sh21.h"
#include <stdio.h>

int             main(int ac, char **av)
{
        (void)ac;
        (void)av;
        if ((tgetent(NULL, getenv("TERM"))))
        {
					int column_count = tgetnum("co");
					int line_count = tgetnum("li");
					printf("count {%d, %d}\n", column_count, line_count);
        }

        return (0);
}
