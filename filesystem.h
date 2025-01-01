#ifndef __FILESYSTEM_H__
#define __FILESYSTEM_H__

#define MAGIC_NUMBER 0x4144564350524F47 // ADVCPROG
#define BLOCK_SIZE 1024
#define MAX_MEMORY 16000000 // max 16MB

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    unsigned long MAGIC;
    int num_blocks;
    int num_inode_blocks;
    int num_inodes;
} super_block;

typedef struct {
    unsigned char data[BLOCK_SIZE];
} data_block;

typedef struct { // 64 byte
    char name[43];
    char type;
    int size;
    data_block *direct; // pointer to data_block if size <= BLOCK_SIZE
    data_block *indirect; // pointer to indirect data_block
} inode;

typedef struct {
    super_block *super;
    data_block *data;  
} fs_ref;

void load_file_system();

#endif