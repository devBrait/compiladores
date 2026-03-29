#include <stdio.h>
#include <stdbool.h>

bool verifica_par_de_as(const char *palavra) {
    int estado = 0; // 0 representa os estados do automato
    int i = 0;
    char caractere;

    while ((caractere = palavra[i]) != '\0') {
        
        switch (estado) {
            case 0: // Estamos em q0 (Quantidade Par)
                if (caractere == 'a')
                    estado = 1; // Transição para q1
                else if (caractere == 'b')
                    estado = 0; // Permanece em q0
                else
                    return false;
                break;
                
            case 1: // Estamos em q1 (Quantidade Ímpar)
                if (caractere == 'a')
                    estado = 0; // Transição de volta para q0
                else if (caractere == 'b')
                    estado = 1; // Permanece em q1
                else
                    return false;
                break;
        }
        i++; // Avança para o próximo caractere da string
    }

    // Após consumir toda a fita de entrada, verifica se parou no estado final
    if (estado == 0) return true; // Aceita (Parou em q0)
    else return false; // Rejeita (Parou em q1, a palavra tem um número ímpar de 'a's)
}

int main() {
    const char *teste1 = "bbababa"; 
    const char *teste2 = "bbabaaba";
    const char *teste3 = "bbbb";

    printf("Teste 1 ('%s'): %s\n", teste1, verifica_par_de_as(teste1) ? "Aceito" : "Rejeitado");
    printf("Teste 2 ('%s'): %s\n", teste2, verifica_par_de_as(teste2) ? "Aceito" : "Rejeitado");
    printf("Teste 3 ('%s'): %s\n", teste3, verifica_par_de_as(teste3) ? "Aceito" : "Rejeitado");

    return 0;
}