#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

extern void convert_image(uint8_t* input, double* output, int height, int width);

void print_usage() {
    printf("Usage:\n");
    printf("  ./main                # manual input mode\n");
    printf("  ./main <file.txt>     # input from comma-separated file\n");
}

int parse_csv_line(uint8_t* dest, char* line, int expected_count, int line_num) {
    char* token = strtok(line, ",");
    int count = 0;

    while (token && count < expected_count) {
        int value = atoi(token);
        if (value < 0 || value > 255) {
            printf("Invalid grayscale value on line %d, value %d\n", line_num, value);
            return -1;
        }
        dest[count++] = (uint8_t)value;
        token = strtok(NULL, ",");
    }

    if (count != expected_count) {
        printf("Incorrect number of values on line %d (expected %d, got %d)\n", line_num, expected_count, count);
        return -1;
    }

    return 0;
}

int main(int argc, char* argv[]) {
    int height, width;
    uint8_t* input;
    double* output;

    if (argc == 2) {
        // === File Input Mode ===
        FILE* file = fopen(argv[1], "r");
        if (!file) {
            perror("Error opening file");
            return 1;
        }

        if (fscanf(file, "%d %d\n", &height, &width) != 2) {
            printf("Invalid file format: expected height and width on first line.\n");
            fclose(file);
            return 1;
        }

        int total = height * width;
        input = malloc(total);
        output = malloc(total * sizeof(double));

        if (!input || !output) {
            printf("Memory allocation failed.\n");
            return 1;
        }

        char* line = NULL;
        size_t len = 0;
        size_t read;
        int row = 0;

        while ((read = getline(&line, &len, file)) != -1 && row < height) {
            if (parse_csv_line(&input[row * width], line, width, row + 2) != 0) {
                free(line);
                free(input);
                free(output);
                fclose(file);
                return 1;
            }
            row++;
        }

        free(line);
        fclose(file);

        if (row != height) {
            printf("Expected %d rows, but only %d were provided.\n", height, row);
            free(input);
            free(output);
            return 1;
        }

    }
    else if (argc == 1) {
        // === Manual Input Mode ===
        printf("Manual input mode.\n");
        printf("Enter height and width: ");
        scanf("%d %d", &height, &width);
        getchar(); // consume newline

        int total = height * width;
        input = malloc(total);
        output = malloc(total * sizeof(double));

        if (!input || !output) {
            printf("Memory allocation failed.\n");
            return 1;
        }

        printf("Enter %d rows with %d comma-separated values (0–255):\n", height, width);
        char line[4096]; // adjust for long rows

        for (int i = 0; i < height; i++) {
            printf("Row %d: ", i + 1);
            if (!fgets(line, sizeof(line), stdin)) {
                printf("Error reading row %d\n", i + 1);
                return 1;
            }

            if (parse_csv_line(&input[i * width], line, width, i + 1) != 0) {
                return 1;
            }
        }

    }
    else {
        print_usage();
        return 1;
    }

    // === Call NASM Conversion Function ===
    convert_image(input, output, height, width);

    // === Print Result (First 5x5 Block) ===
    printf("\nConverted Output (first 5x5 block):\n");
    for (int i = 0; i < height && i < 5; i++) {
        for (int j = 0; j < width && j < 5; j++) {
            printf("%.2f ", output[i * width + j]);
        }
        printf("\n");
    }

    free(input);
    free(output);
    return 0;
}
