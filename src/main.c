#include <stdio.h>
#include <stdlib.h>

void hex(char *buffer, int file_size)
{
    int itterator = 0;
    while (itterator < file_size)
    {
        for (size_t n = 0; (n + itterator) != (itterator + 16); n++)
        {
            if (n + itterator >= file_size)
            {
                for (; n < 16; n++)
                {
                    printf("  ");
                    if (n % 2 == 1 && n != 0)
                    {
                        printf(" ");
                    }
                }
                break;
            }
            printf("%02x", buffer[n + itterator]);
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
                for (; n < 16; n++)
                {
                    printf(" ");
                }
                break;
            }
            if (buffer[n + itterator] == '\n')
            {
                printf(".");
            }
            else
            {
                printf("%c", buffer[n + itterator]);
            }
        }
        printf(" |");
        printf("\n");
        itterator += 16;
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

    char *buffer = calloc(eof, sizeof(char) * eof);
    size_t ret_code = fread(buffer, sizeof(char), eof, open_file);

    if (ret_code == (eof - 1))
    {
        hex(buffer, eof - 1);
    }
    return 0;
}