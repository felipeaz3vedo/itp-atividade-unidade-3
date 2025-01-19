#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "barcode_utils.h"

#define DEFAULT_SPACING 4
#define DEFAULT_AREA_WIDTH 3
#define DEFAULT_HEIGHT 100
#define OUTPUT_DIR "bar-codes"

char *generate_output_filename()
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    char *filename = malloc(256);

    if (filename)
    {
        snprintf(
            filename,
            256,
            "%s/bar-code_%04d%02d%02d%02d%02d%02d.pbm",
            OUTPUT_DIR,
            tm.tm_year + 1900,
            tm.tm_mon + 1,
            tm.tm_mday,
            tm.tm_hour,
            tm.tm_min,
            tm.tm_sec);
    }
    
    return filename;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Uso: %s <identificador> [espacamento] [largura_area] [altura]\n", argv[0]);
        return 1;
    }

    char *identifier = argv[1];
    int spacing = (argc > 2) ? atoi(argv[2]) : DEFAULT_SPACING;
    int area_width = (argc > 3) ? atoi(argv[3]) : DEFAULT_AREA_WIDTH;
    int height = (argc > 4) ? atoi(argv[4]) : DEFAULT_HEIGHT;

    if (!is_valid_identifier(identifier))
    {
        printf("Identificador inválido. Certifique-se de que ele contém 8 dígitos válidos e que o dígito verificador esteja correto.\n");
        return 1;
    }

    char *output_file = generate_output_filename();

    if (!output_file)
    {
        printf("Erro ao gerar o nome do arquivo de saída.\n");
        return 1;
    }

    if (generate_barcode_image(identifier, spacing, area_width, height, output_file))
    {
        printf("Imagem de código de barras gerado com sucesso em %s.\n", output_file);
    }
    else
    {
        printf("Erro ao gerar a imagem do código de barras.\n");
    }

    free(output_file);

    return 0;
}