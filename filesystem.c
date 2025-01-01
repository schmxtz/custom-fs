#include <stdio.h>
#include <stdlib.h>

#include "filesystem.h"

fs_ref * load_file_system(const char *file_name, int partition_size) {
    super_block *super = (super_block *) malloc(sizeof(super_block));
    data_block* data;

    if(file_name == NULL) {
        super = (super_block *) malloc(sizeof(super_block));
        if(partition_size < 0 || partition_size > MAX_MEMORY) exit(-1);
        super->MAGIC = MAGIC_NUMBER;
        int total_block_count = calc_block_count(partition_size);
        super->num_inode_blocks = (int) total_block_count / 10; // 10% of blocks for inodes
        super->num_blocks = total_block_count - super->num_inode_blocks; // remaining blocks for data
        super->num_inodes = 0;
        data = (data_block *) malloc(total_block_count * sizeof(data_block));
    } else {
        FILE *fptr = fopen(file_name, "rb");
        if(fptr == NULL) exit(-2);
        fread(super, sizeof(super_block), 1, fptr);
        data = (data_block *) malloc((super->num_blocks + super->num_inode_blocks) * sizeof(data_block));
        fread(data, sizeof(data_block), (super->num_blocks + super->num_inode_blocks), fptr);
        fclose(fptr);
    }
    fs_ref *ref = (fs_ref *) malloc(sizeof(fs_ref));
    ref->super = super;
    ref->data = data;
}

void dump_file_system(fs_ref *ref) {
    FILE *fptr = fopen("my_fs.dump", "wb");
    if(fptr == NULL) exit(-3);
    fwrite(ref->super, sizeof(super_block), 1, fptr);
    fwrite(ref->data, sizeof(data_block), ref->super->num_blocks, fptr);
    fclose(fptr);
}

int calc_block_count(int partition_size) {
    int remaining_space = partition_size - sizeof(super_block);
    return (int) (remaining_space - (remaining_space % BLOCK_SIZE)) / BLOCK_SIZE;
}
