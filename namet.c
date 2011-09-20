#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <sys/stat.h>

#define LOWER "lower"
#define UPPER "upper"
#define DYNAMIC "dynamic"
#define FLIP "flip"

void usage() {
    printf("namet <option> <file>\n\n");
    printf("options: \n");
    printf("    upper\tTransform name to uppercase\n");
    printf("    lower\tTransform name to lowercase\n");
    printf("    dynamic\tTransform name to nearest upper/lower-case\n");
    printf("    flip\tFlips all chars. Lowercase becomes uppercase\n");
}

void strtolower(char *str) {
    
    for(;*str;str++) {
        *str = tolower(*str);
    }
}

void strtoupper(char *str) {
    
    for(;*str;str++) {
        *str = toupper(*str);
    }
}

void dynamic_transform(char *str) {
    
    char *begin = str;
    int upper = 0,lower = 0;

    for(;*str;str++) {
        
        if (isupper(*str)) {
            upper++;
        } else {
            lower++;
        }
    }

    if (lower >= upper) {
        strtolower(begin);
    } else {
        strtoupper(begin);
    }
}

void flip(char *str) {
  
    for(;*str;str++) {

        if (isupper(*str)) {
            *str = tolower(*str);
        } else {
            *str = toupper(*str);
        }
    }
}

int main (const int argc, const char **argv) {

    const char *oldname = argv[2];
    char *name = malloc(sizeof(char) * (strlen(oldname)) + 1);
    struct stat st;

    strcpy(name,oldname);

    if (argc != 3) {
        usage();
        return 1;
    }
    
    /* find option */
    if (strcmp(LOWER,argv[1]) == 0) {
        strtolower(name);
    } else if (strcmp(UPPER,argv[1]) == 0) {
        strtoupper(name);
    } else if (strcmp(DYNAMIC, argv[1]) == 0) {
        dynamic_transform(name);
    } else if (strcmp(FLIP, argv[1]) == 0) {
        flip(name);
    }
   
    if ((stat(oldname, &st)) == -1) {
        printf("The file does not exist!\n");
        return -1;
    }

    rename(oldname, name);
    printf("Changed name from %s to %s\n", oldname, name);

    if (name != NULL)
        free(name);

    return 0;
}




