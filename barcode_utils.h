#ifndef BARCODE_UTILS_H
#define BARCODE_UTILS_H

#include <stdbool.h>

bool is_valid_identifier(const char *identifier);
int calculate_check_digit(const char *identifier);
bool generate_barcode_image(const char *identifier, int spacing, int area_width, int height, const char *filename);
bool is_barcode_pixel(const char *identifier, int position);
bool get_left_barcode_pixel(const char *identifier, int position);
bool get_right_barcode_pixel(const char *identifier, int position);

#endif