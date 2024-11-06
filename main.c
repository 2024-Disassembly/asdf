#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#pragma pack(1)

typedef struct {
    char magic_number[4];
    unsigned short width;
    unsigned short height;
    unsigned char color_depth;
} MyImageHeader;

void save_myimg(const char* file_path, unsigned short width, unsigned short height, unsigned char (*pixels)[3]) {
    MyImageHeader header = {"MYIM", width, height, 24};

    FILE *file = fopen(file_path, "wb");
    if (!file) {
        printf("Failed to open file for writing.\n");
        return;
    }

    fwrite(&header, sizeof(MyImageHeader), 1, file);

    for (int i = 0; i < width * height; i++) {
        fwrite(pixels[i], sizeof(unsigned char), 3, file);
    }

    fclose(file);
}

void generate_random_pixels(unsigned short width, unsigned short height, unsigned char (*pixels)[3]) {
    srand((unsigned int)time(NULL));

    for (int i = 0; i < width * height; i++) {
        pixels[i][0] = rand() % 256;  // Red
        pixels[i][1] = rand() % 256;  // Green
        pixels[i][2] = rand() % 256;  // Blue
    }
}

int main() {
    unsigned short width = 500, height = 500;
    unsigned char (*random_pixels)[3] = malloc(width * height * 3);

    generate_random_pixels(width, height, random_pixels);
    save_myimg("asdf.lyc", width, height, random_pixels);

    free(random_pixels);
    return 0;
}
