#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

/* ================================ INCLUDES ================================ */

# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include "libft.h"

/* ================================ DEFINES ================================= */

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# endif

/* ========================== FUNCTION PROTOTYPES =========================== */

/* --- Main function --- */

char	*get_next_line(int fd);

#endif
