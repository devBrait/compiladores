#include <stdio.h>

/* Este eh um comentario
   de multiplas linhas padrao.
   Ele deve sumir completamente. */

int main() {
    // Definindo as variaveis base
    int a = 10;
    
    /* Pegadinha 1: Comentario no meio da declaracao */
    int /* tipo inteiro */ b = 20; 
    
    /* Pegadinha 2: O simbolo de divisao solto nao pode sumir! */
    int divisao = b / a; 
    
    printf("O valor da divisao e: %d\n", divisao);
    
    /** Pegadinha 3: Muitos asteriscos seguidos ( /***/ ) ***/
    
    return 0; /* Fim do programa */
}