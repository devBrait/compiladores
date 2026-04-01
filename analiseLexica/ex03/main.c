#include <stdio.h>
#include <stdbool.h>

bool analisa_expressao(const char *palavra) {

    int estado = 0; // Começa no estado inicial q0
    int i = 0;
    char caractere;

    while ((caractere = palavra[i]) != '\0') {
            switch(estado){
                case 0:
                    if(caractere == 'a') estado = 1;
                    else return false;
                break;
                case 1:
                    if(caractere == 'a') estado = 5;
                    else if(caractere == 'b') estado = 4;
                    else if(caractere == 'c') estado = 2;
                    else return false;
                break;
                case 2:
                    if(caractere == 'a') estado = 3;
                    else if(caractere == 'b') estado = 3;
                    else return false;
                break;
                case 3:
                    if(caractere == 'c') estado = 6;
                    else return false;
                break;
                case 4:
                    if(caractere == 'a') estado = 1;
                    else return false;
                break;
                case 5:
                    if(caractere == 'b') estado = 1;
                    else return false;
                break;
                case 6:
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