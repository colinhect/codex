#include "types.h"
#include "bytecode.h"
#include "file.h"

#include "machine.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void usage(void) {
    fprintf(stderr, "usage: codex executable\n");
}

int main(int argc, const char* argv[]) {
    int_t filename = 0;
    int_t debug = 0;

    int_t i;
    for (i = 0; i < argc; ++i) {
        if (strcmp(argv[i], "-d") == 0) {
            debug = 1;
        } else {
            filename = i;
        }
    }

    byte_t* code = load_bytecode(argv[filename]);

    if(code == NULL) {
        fprintf(stderr, "invalid executable\n");
        usage();
        return 0;
    }

    execute(code, debug);
    free(code);

    return 0;
}
