#include <stdio.h>
#include <stdbool.h>

bool analisa_expressao(const char *palavra) {

    int estado = 0; // Começa no estado inicial q0
    int i = 0;
    char caractere;

    while ((caractere = palavra[i]) != '\0') {
        
        switch (estado) {
            case 0: // q0: Espera o 'a' inicial
                if (caractere == 'a') estado = 1;
                else return false; // Cai no estado de erro e já encerra
                break;
                
            case 1: // q1: Aonde acontece o loop
                if (caractere == 'a') estado = 2;      // Inicia bloco 'ab'
                else if (caractere == 'b') estado = 3; // Inicia bloco 'ba'
                else if (caractere == 'c') estado = 4; // Vai para a reta final
                else return false;
                break;
                
            case 2: // q2: Esperando o 'b' para fechar o bloco 'ab'
                if (caractere == 'b') estado = 1; // Volta pro hub
                else return false;
                break;
                
            case 3: // q3: Esperando o 'a' para fechar o bloco 'ba'
                if (caractere == 'a') estado = 1; // Volta pro hub
                else return false;
                break;
                
            case 4: // q4: Leu o primeiro 'c', agora exige 'a' OU 'b'
                if (caractere == 'a' || caractere == 'b') estado = 5;
                else return false;
                break;
                
            case 5: // q5: Leu o (a|b), agora exige o 'c' final
                if (caractere == 'c') estado = 6;
                else return false;
                break;
                
            case 6: // q6: Estado Final. Se tiver mais letras depois, é erro!
                return false; 
        }
        i++;
    }

    if (estado == 6) return true;
    else return false; 
}

int main() {
    const char *teste = "acac";
    printf("%s\n", analisa_expressao(teste) ? "Aceito" : "Rejeitado");

    return 0;
}