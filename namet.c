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

char *bname(const char *path) {
    
    char *file;
    
    file = strrchr(path, '/');
    
    if (file == NULL) 
        file = (char *)path;
    else 
        ++file;

    return file;
}

int main (const int argc, const char **argv) {

    const char *pathOld = argv[2];
    char *pathNew = malloc(sizeof(char) * (strlen(pathOld)) + 1);
    char *nameOld = bname(pathOld);
    char *nameNew;
    struct stat st;
    
    strcpy(pathNew,pathOld);

    nameNew = bname(pathNew);

    if (argc != 3) {
        usage();
        return 1;
    }
    
    /* file exists? */
    if ((stat(pathOld, &st)) == -1) {
        printf("The file does not exist!\n");
        return -1;
    }
    
    /* find option */
    if (strcmp(LOWER,argv[1]) == 0) {
        strtolower(nameNew);
    } else if (strcmp(UPPER,argv[1]) == 0) {
        strtoupper(nameNew);
    } else if (strcmp(DYNAMIC, argv[1]) == 0) {
        dynamic_transform(nameNew);
    } else if (strcmp(FLIP, argv[1]) == 0) {
        flip(nameNew);
    } 

    /* rename file */
    rename(pathOld, pathNew);
    printf("Changed name from %s to %s\n", nameOld, nameNew);
    
    /* cleanup */
    if (pathNew != NULL)
        free(pathNew);

    return 0;
}




