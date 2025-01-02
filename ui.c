#include <stdio.h>
#include <stdlib.h>

#include "ui.h"

void ui_main_menu() {
    filesystem * fs;
    int option;

    printf("Options:\n  1. Load partition from file\n  2. Create new partition in memory\n  Choose option?: ");
    scanf("%d", &option);
    switch (option) {
    case 1:
        char file_name[32];
        printf("\nSpecify the partition name on disk: ");
        scanf("%s", file_name);
        fs = load_filesystem(file_name, 0);
        break;
    case 2:
        int partition_size;
        printf("\nSpecify the partition size: ");
        scanf("%d", &partition_size);
        fs = load_filesystem(NULL, partition_size);
        break;
    default:
        printf("Invalid choice!\n");
        ui_main_menu();
        break;
    }
}