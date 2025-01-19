#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "barcode_utils.h"

#define DEFAULT_SPACING 4
#define DEFAULT_AREA_WIDTH 3
#define DEFAULT_HEIGHT 100
#define OUTPUT_DIR "bar-codes"
#define FILE_EXTENSION ".pbm"

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
            "%s/bar-code_%04d%02d%02d%02d%02d%02d%s",
            OUTPUT_DIR,
            tm.tm_year + 1900,
            tm.tm_mon + 1,
            tm.tm_mday,
            tm.tm_hour,
            tm.tm_min,
            tm.tm_sec,
            FILE_EXTENSION);
    }
    return filename;
}

bool file_exists(const char *filename)
{
    FILE *file = fopen(filename, "r");

    if (file)
    {
        fclose(file);
        return true;
    }

    return false;
}

bool is_numeric(const char *str)
{
    for (int i = 0; str[i] != '\0'; ++i)
    {
        if (str[i] < '0' || str[i] > '9')
        {
            return false;
        }
    }

    return true;
}

char *ensure_extension(const char *filename, const char *extension)
{
    size_t len = strlen(filename);
    size_t ext_len = strlen(extension);

    if (len >= ext_len && strcmp(filename + len - ext_len, extension) == 0)
    {
        return strdup(filename);
    }
    else
    {
        char *filename_with_ext = malloc(len + ext_len + 1);

        if (filename_with_ext)
        {
            snprintf(filename_with_ext, len + ext_len + 1, "%s%s", filename, extension);
        }
        return filename_with_ext;
    }
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Uso: %s <identificador> [espacamento] [largura_area] [altura] [nome_arquivo]\n", argv[0]);
        return 1;
    }

    char *identifier = argv[1];

    if (!is_numeric(identifier))
    {
        printf("Erro: O identificador deve conter apenas valores numéricos.\n");
        return 1;
    }

    int spacing = (argc > 2) ? atoi(argv[2]) : DEFAULT_SPACING;
    int area_width = (argc > 3) ? atoi(argv[3]) : DEFAULT_AREA_WIDTH;
    int height = (argc > 4) ? atoi(argv[4]) : DEFAULT_HEIGHT;

    char *output_file = NULL;

    if (argc > 5)
    {
        char *provided_name = argv[5];
        char *temp_file = ensure_extension(provided_name, FILE_EXTENSION);

        if (temp_file)
        {
            output_file = malloc(strlen(OUTPUT_DIR) + strlen(temp_file) + 2);
            if (output_file)
            {
                snprintf(output_file, strlen(OUTPUT_DIR) + strlen(temp_file) + 2, "%s/%s", OUTPUT_DIR, temp_file);
            }
            free(temp_file);
        }
    }
    else
    {
        output_file = generate_output_filename();
    }

    if (!output_file)
    {
        printf("Erro ao gerar o nome do arquivo de saída.\n");
        return 1;
    }

    if (!is_valid_identifier(identifier))
    {
        printf("Identificador inválido. Certifique-se de que ele contém 8 dígitos válidos e que o dígito verificador esteja correto.\n");
        free(output_file);

        return 1;
    }

    if (file_exists(output_file))
    {
        printf("O arquivo %s já existe. Deseja sobrescrevê-lo? (s/n): ", output_file);

        char resposta;

        scanf(" %c", &resposta);

        if (resposta != 's' && resposta != 'S')
        {
            printf("Arquivo resultante já existe. Execução encerrada.\n");
            free(output_file);
            return 1;
        }
    }

    if (generate_barcode_image(identifier, spacing, area_width, height, output_file))
    {
        printf("Imagem de código de barras gerada com sucesso em %s.\n", output_file);
    }
    else
    {
        printf("Erro ao gerar a imagem do código de barras.\n");
        free(output_file);
        return 1;
    }

    free(output_file);
    return 0;
}