#include <stdio.h>

int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        printf("Usage: cp source destination\n");
        return 1;
    }

    // TODO: copy the contents of argv[1] to argv[2]
    FILE *original, *copy;
    char buffer[512];
    
    original = fopen( argv[1], "r");
    copy = fopen( argv[2], "w");
    
    while( fgets(buffer, sizeof(buffer), original) != NULL )
    {
        fprintf(copy, "%s", buffer);
    }
    
    fclose(copy);
    fclose(original);
    return 0;
}

