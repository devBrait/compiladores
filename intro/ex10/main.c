#include <stdio.h>

int main() {
    FILE *file = fopen("ex10.c", "r");
    
    if (file == NULL) {
        printf("Erro na importacao do file\n");
        return 1;
    }

    int count;
    int keyBalance = 0;
    int error = 0;

    while ((count = fgetc(file)) != EOF) {
        
        if (count == '{') {
            keyBalance++; // Empilha (abre uma nova chave)
        } 
        else if (count == '}') {
            keyBalance--; // Desempilha (fecha a última chave aberta)
        
            // Se o saldo ficar negativo, fechou uma chave a mais.
            if (keyBalance < 0) {
                error = 1;
                break;
            }
        }
    }

    fclose(file);

    if (error == 1) 
        printf("Erro de Sintaxe: Voce fechou uma chave '}' que nao havia sido aberta.\n");
    else if (keyBalance > 0)
        printf("Erro de Sintaxe: Faltou fechar %d chave(s) no final do codigo.\n", keyBalance);
    else 
        printf("Sucesso: Todas as chaves estao aninhadas perfeitamente!\n");

    return 0;
}