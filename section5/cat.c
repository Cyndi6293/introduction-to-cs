#include <stdio.h>

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        printf("Usage: cat filename [filename ...]\n");
        return 1;
    }

    for (int i = 1; i < argc; i++)
    {
        FILE* ff;
        ff = fopen( argv[i], "r");
        char buffer[256];
        for (int line = 0; fgets(buffer, sizeof(buffer), ff) != NULL; line++)
        {
            printf("%s", buffer);
        }
        fclose(ff);       
        
    }

    return 0;
}

