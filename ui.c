#include <stdio.h>
#include <stdlib.h>

#include "ui.h"

void ui_main_menu() {
    int option;
    fs_ref * ref;
    printf("Options:\n  1. Load partition from file\n  2. Create new partition in memory\n  Choose option?: ");
    scanf("%d", &option);
    switch (option) {
    case 1:
        char *file_name;
        printf("\nSpecify the partition name on disk: ");
        scanf("%s", &file_name);
        ref = load_file_system(file_name, 0);
        dump_file_system(ref);
        break;
    case 2:
        int partition_size;
        printf("\nSpecify the partition size: ");
        scanf("%d", &partition_size);
        ref = load_file_system(NULL, partition_size);
        dump_file_system(ref);
        break;
    default:
        printf("Invalid choice!\n");
        ui_main_menu();
        break;
    }
}