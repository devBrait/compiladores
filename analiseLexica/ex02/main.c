#include <stdio.h>
#include <stdbool.h>

bool verifica_sem_aa(const char *palavra) {
    
    int estado = 0;
    int i = 0;
    char caractere;

    while ((caractere = palavra[i]) != '\0') {
        
        switch (estado) {
            case 0: // Estado q0: Seguro
                if (caractere == 'a')
                    estado = 1; // Liga o alerta (vai para q1)
                else if (caractere == 'b')
                    estado = 0; // Continua seguro
                else
                    return false; 
                break;
                
            case 1: // Estado q1: Alerta
                if (caractere == 'a')
                    estado = 2; // Leu 'aa'! Cai no Estado Morto (q2)
                else if (caractere == 'b')
                    estado = 0; // O 'b' salvou! Volta a ficar seguro em q0
                else
                    return 0;
                break;
                
            case 2:
                break;
        }
        i++;
    }

    if (estado == 0 || estado == 1) return true;
    else return false; 
}

int main() {

    const char *teste1 = "baba";
    const char *teste2 = "baab";
    const char *teste3 = "a";
    const char *teste4 = "bbbaa";
    
    printf("Teste '%s': %s\n", teste1, verifica_sem_aa(teste1) ? "Aceito" : "Rejeitado");
    printf("Teste '%s': %s\n", teste2, verifica_sem_aa(teste2) ? "Aceito" : "Rejeitado");
    printf("Teste '%s': %s\n", teste3, verifica_sem_aa(teste3) ? "Aceito" : "Rejeitado");
    printf("Teste '%s': %s\n", teste4, verifica_sem_aa(teste4) ? "Aceito" : "Rejeitado");

    return 0;
}