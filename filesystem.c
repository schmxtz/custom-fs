#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "filesystem.h"


filesystem * load_filesystem(const char *file_name, int partition_size) {
    filesystem *fs = (filesystem *) malloc(sizeof(filesystem));
    superblock *super = (superblock *) malloc(sizeof(superblock));

    if(file_name == NULL) { // Create fresh filesystem
        memcpy(&(super->MAGIC), &(MAGIC_NUMBER), sizeof(MAGIC_NUMBER));
        printf("%d", partition_size);
        printf("%s", super->MAGIC);
    } else {

    }
    return NULL;
}

void dump_filesystem(filesystem *fs) {

}