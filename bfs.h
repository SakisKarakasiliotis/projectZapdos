#ifndef BFS_H
#define BFS_H

#include "defines.h"
#include "index.h"
#include "buffer.h"

int BBFS(n_index*, buffer*, uint32_t, n_index*, buffer*, uint32_t, int);
int DBBFS(n_index*, buffer*, uint32_t, n_index*, buffer*, uint32_t, int, int);
OK_SUCCESS GetConnectedComponents(n_index*, buffer*, n_index*, buffer*);
#endif
