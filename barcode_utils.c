#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

static const int L_CODES[10] = {0b0001101, 0b0011001, 0b0010011, 0b0111101, 0b0100011, 
                               0b0110001, 0b0101111, 0b0111011, 0b0110111, 0b0001011};
static const int R_CODES[10] = {0b1110010, 0b1100110, 0b1101100, 0b1000010, 0b1011100, 
                               0b1001110, 0b1010000, 0b1000100, 0b1001000, 0b1110100};

bool get_left_barcode_pixel(const char *identifier, int position);
bool get_right_barcode_pixel(const char *identifier, int position);
bool is_barcode_pixel(const char *identifier, int position);
int calculate_check_digit(const char *identifier);

bool get_left_barcode_pixel(const char *identifier, int position) {
    int digit = (position - 3) / 7;
    int bit = (position - 3) % 7;
    int left_barcode_value = L_CODES[identifier[digit] - '0'];
    int mask = (1 << (6 - bit));
    
    bool is_pixel_on = (left_barcode_value & mask) != 0;
    
    return is_pixel_on;
}

bool get_right_barcode_pixel(const char *identifier, int position) {
    int digit = (position - 36) / 7;
    int bit = (position - 36) % 7;
    int right_barcode_value = R_CODES[identifier[digit + 4] - '0'];
    int mask = (1 << (6 - bit));
    
    bool is_pixel_on = (right_barcode_value & mask) != 0;
    
    return is_pixel_on;
}

bool is_barcode_pixel(const char *identifier, int position) {
    static const char *markers[] = {"101", "01010", "101"};
    
    if (position < 3) {
        return markers[0][position] - '0';
    }
    else if (position < 31) {
        return get_left_barcode_pixel(identifier, position);
    }
    else if (position < 36) {
        return markers[1][position - 31] - '0';
    }
    else if (position < 64) {
        return get_right_barcode_pixel(identifier, position);
    }
    else {
        return markers[2][position - 64] - '0';
    }
}

int calculate_check_digit(const char *identifier) {
    int sum = 0;
    
    for (int i = 0; i < 7; ++i) {
        int weight = (i % 2 == 0) ? 3 : 1;
        sum += weight * (identifier[i] - '0');
    }
    
    return (10 - (sum % 10)) % 10;
}

bool is_valid_identifier(const char *identifier) {
    if (strlen(identifier) != 8)
        return false;
    
    for (int i = 0; i < 8; ++i) {
        if (identifier[i] < '0' || identifier[i] > '9')
            return false;
    }
    
    int check_digit = calculate_check_digit(identifier);
    
    return (identifier[7] - '0') == check_digit;
}

bool generate_barcode_image(const char *identifier, int spacing, int area_width, int height, const char *filename) {
    FILE *file = fopen(filename, "w");
    
    if (!file) {
        return false;
    }
    
    int barcode_width = 3 + 28 + 5 + 28 + 3;
    int image_width = spacing * 2 + barcode_width * area_width;
    int image_height = height + spacing * 2;
    
    fprintf(file, "P1\n%d %d\n", image_width, image_height);
    
    for (int y = 0; y < image_height; ++y) {
        for (int x = 0; x < image_width; ++x) {
            bool is_within_bars_area = (y >= spacing && y < spacing + height && x >= spacing && x < (spacing + barcode_width * area_width));
            
            if (!is_within_bars_area) {
                fprintf(file, "0 ");
            }
            else {
                int barcode_x = (x - spacing) / area_width;
                int is_barcode_pixel_value = is_barcode_pixel(identifier, barcode_x);
                
                fprintf(file, "%d ", is_barcode_pixel_value);
            }
        }
        
        fprintf(file, "\n");
    }
    
    fclose(file);
    return true;
}