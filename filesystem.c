#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "filesystem.h"


filesystem * load_filesystem(const char *file_name, int partition_size) {
    filesystem *fs = (filesystem *) malloc(sizeof(filesystem));
    superblock *super = (superblock *) malloc(sizeof(superblock));

    if(file_name == NULL) { // Create fresh filesystem
        memcpy(&(super->MAGIC), &(MAGIC_NUMBER), sizeof(MAGIC_NUMBER));
        super->partitition_size = partition_size;
        int remaining_space = partition_size - sizeof(superblock);
        super->total_blocks = (int) (remaining_space / sizeof(data_block));
        super->total_data_blocks = (int) super->total_blocks * 0.9; // 90% of space for data blocks
        super->used_blocks = 0;
        super->total_inodes_blocks = super->total_blocks - super->total_data_blocks;
        super->total_inodes = (int) super->total_inodes_blocks * (BLOCK_SIZE / sizeof(inode)); // 10% of space for inode blocks
        super->used_inodes = 0;
        int inodes_per_block = BLOCK_SIZE / sizeof(inode);
        super->inode_blocks = (inode_block *) malloc(sizeof(inode_block) * super->total_inodes_blocks);
        // init inodes to be free
        for(int i = 0; i < super->total_inodes_blocks; i++) {
            for(int j = 0; j < inodes_per_block; j++) {
                super->inode_blocks[i].inodes[j].type = FREE_INODE;
            }
        }
        super->data_blocks = (data_block *) malloc(sizeof(data_block) * super->total_blocks);
    } else {
        FILE *fptr = fopen(file_name, "rb");
        fread(super, sizeof(superblock), 1, fptr);
        super->inode_blocks = (inode_block *) malloc(sizeof(inode_block) * super->total_inodes_blocks);
        fread(super->inode_blocks, sizeof(inode_block), super->total_inodes_blocks, fptr);
        printf("MAGIC: %s\n", super->MAGIC);
        printf("partition_size: %d\n", super->partitition_size);
        printf("total_blocks: %d\n", super->total_blocks);
        printf("used_blocks: %d\n", super->used_blocks);
        printf("total_inodes: %d\n", super->total_inodes);
        printf("used_inodes: %d\n", super->used_inodes);
        printf("total_inodes_blocks: %d\n", super->total_inodes_blocks);
        int inodes_per_block = BLOCK_SIZE / sizeof(inode);
        for(int i = 0; i < super->total_inodes_blocks; i++) {
            for(int j = 0; j < inodes_per_block; j++) {
                printf("%s", super->inode_blocks[i].inodes[j].name);
                printf("%d", super->inode_blocks[i].inodes[j].type);
            }
        }
        fread(super->data_blocks, sizeof(data_block), super->total_data_blocks, fptr);
        fclose(fptr);
    }
    fs->super = super;
    return fs;
}

void dump_filesystem(filesystem *fs) {
    FILE *fptr = fopen("my_fs.dump", "wb");
    fwrite(fs->super, sizeof(superblock), 1, fptr);
    int inodes_per_block = BLOCK_SIZE / sizeof(inode);
    for(int i = 0; i < fs->super->total_inodes_blocks; i++) {
        for (int j = 0; j < inodes_per_block; j++) 
            fwrite(&(fs->super->inode_blocks[i].inodes[j]), sizeof(inode), 1, fptr);
    }
    for(int i = 0; i < fs->super->total_data_blocks; i++) {
        fwrite(&(fs->super->data_blocks[i]), sizeof(data_block), 1, fptr);
    }
    fclose(fptr);
}