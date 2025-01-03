#ifndef __FILESYSTEM_H__
#define __FILESYSTEM_H__

#define POINTER_SIZE_BYTES sizeof(void *)
#define MAGIC_NUMBER "ADV C-PROG 2024"
#define BLOCK_SIZE 1024
#define MAX_MEMORY 16000000 // max 16MB
#define NAME_MAX_LEN 15

enum file_type {
    FREE_INODE,
    FILE_INODE,
    DIRECTORY_INODE
};

typedef struct {
    char name[NAME_MAX_LEN]; // 15 chars for alignment (14 chars + null terminate)
    enum file_type type;
    int file_size;
    int direct_index; // will be the parent index for directories
    int indirect_indices; // will be the children indices inside directories
} inode;

typedef struct {
    inode inodes[BLOCK_SIZE/sizeof(inode)];
} inode_block;

typedef struct {
    char data[BLOCK_SIZE];
} data_block;

typedef struct {
    int block_indices[BLOCK_SIZE / sizeof(int)];
} indirect_data_block;

typedef struct {
    char MAGIC[16];
    data_block *data_blocks;
    inode_block *inode_blocks;
    int partitition_size;
    int total_inodes;
    int used_inodes;
    int total_inodes_blocks;
    int total_data_blocks;
    int total_blocks;
    int used_blocks;
} superblock;

typedef struct {
    superblock *super;
    int *free_block_bitmap;
} filesystem;

filesystem *load_filesystem(const char *file_name, int partition_size);
void dump_filesystem(filesystem *fs);

#endif