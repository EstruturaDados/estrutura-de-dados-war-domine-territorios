#include <stdlib.h>
#include "liberarMemoria.h"

void liberarMemoria() {
    extern Territorio *t;
    free(t); // Libera a memoria alocada para os territorios
    t = NULL;
}
