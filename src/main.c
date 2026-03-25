#include <stdio.h>
#include <stdlib.h>

enum
{
    LINE_LENGTH = 60
};

int round_up(int value)
{
    value--;
    value |= value >> 1;
    value |= value >> 2;
    value |= value >> 4;
    value |= value >> 8;
    value |= value >> 16;
    value++;
    return value;
}

void hex(char *buffer, int file_size)
{
    int itterator = 0;
    int new_lines = 0;
    int maxmimum = round_up(file_size);
    int lines = maxmimum / 16;
    while (new_lines != lines)
    {
        for (size_t n = 0; (n + itterator) != (itterator + 16); n++)
        {
            if (n + itterator >= file_size)
            {
                for (int blank = (maxmimum - file_size) - 1; blank > 0; blank--)
                {
                    printf("   ");
                }
                break;
            }
            printf("%x", buffer[n + itterator]);
            if (n % 2 == 1 && n != 0)
            {
                printf(" ");
            }
        }

        printf("| ");
        for (size_t n = 0; (n + itterator) != (itterator + 16); n++)
        {
            if (n + itterator >= file_size)
            {
                for (int blank = (maxmimum - file_size); blank > 0; blank--)
                {
                    printf(" ");
                }
                break;
            }
            printf("%c", buffer[n + itterator]);
        }
        printf(" |");
        printf("\n");
        itterator = 16;
        new_lines++;
    }
}

int main(int argc, char *argv[])
{
    char *file_name = argv[1];
    fpos_t pos;
    long eof;

    FILE *open_file = fopen(file_name, "rb");
    if (fseek(open_file, sizeof(char), SEEK_END) == 0)
    {
        fgetpos(open_file, &pos);
        eof = pos.__pos;
        fseek(open_file, 0, SEEK_SET);
    }
    printf("eof %ld\n", eof);
    char *buffer = calloc(eof, sizeof(char) * eof);
    size_t ret_code = fread(buffer, sizeof(char), eof, open_file);

    if (ret_code == (eof - 1))
    {
        hex(buffer, eof - 1);
    }
    return 0;
}