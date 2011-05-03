#include "file.h"

#include <stdio.h>
#include <stdlib.h>

byte_t* load_bytecode(const char* filename) {

    /* Load the file and check for error */
    FILE* fp = fopen(filename, "rb");
    if(fp == NULL)
        return NULL;

    size_t res = 0;

    /* Verify magic number */ 
    int_t magic = 0;
    res = fread(&magic, 8, 1, fp);
    if(magic != 987 || res != 1) {
        fclose(fp);
        return NULL;
    }

    /* Read the length */
    int_t len = 0;
    res = fread(&len, 8, 1, fp);
    if(res != 1) {
        fclose(fp);
        return NULL;
    }

    /* Allocate space and load the code */
    byte_t* code = (byte_t*) calloc(len, 1);
    res = fread(code, 1, len, fp);
    if(res != len) {
        fclose(fp);
        return NULL;
    }

    /* Close the file and return the code */
    fclose(fp);
    return code;
}

int save_bytecode(const char* filename, byte_t* code, int_t len) {

    /* Load the file and check for error */
    FILE* fp = fopen(filename, "wb");
    if(fp == NULL)
        return 0;

    /* Write the magic number */ 
    int_t magic = 987;
    fwrite(&magic, 8, 1, fp);

    /* Write the code length */
    fwrite(&len, 8, 1, fp);

    /* Write the code */
    fwrite(code, 1, len, fp);

    /* Close the file and return success */
    fclose(fp);
    return 1;
}

