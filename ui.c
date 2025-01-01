#include <stdio.h>
#include <stdlib.h>

#include "ui.h"
#include "filesystem.h"

void ui_main_menu() {
    int option = -1;
    printf("Options:\n  1. Load partition from file\n  2. Create new partition in memory\n  Choose option?: ");
    scanf("%d", &option);
    switch (option) {
    case 1:
        load_file_system()
        break;
    case 2:
        printf("%d", option);
        break;
    default:
        printf("Invalid choice!\n");
        ui_main_menu();
        break;
    }
}