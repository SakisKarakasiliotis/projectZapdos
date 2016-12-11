//
// Created by Marcus on 11/12/2016.
//

#ifndef STATICBFS_H
#define STATICBFS_H

#include "index.h"
#include "buffer.h"
#include "grail.h"
#include "defines.h"

int SBBFS(grail* holy, n_index* outIndex, buffer* outgoing, uint32_t start, n_index* inIndex, buffer* incoming, uint32_t dest, int fringeSize);

#endif //STATICBFS_H
