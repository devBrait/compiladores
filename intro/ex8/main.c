#include <stdio.h>

int main() {
    FILE *file = fopen("ex8.txt", "r");

    int current;
    int maiusculas = 0;
    int minusculas = 0;
    int digitos = 0;
    int espacos = 0;

    if (file == NULL) {
        printf("Erro na importação do file\n");
        return 1;
    }

    while ((current = fgetc(file)) != EOF) {
        if (current >= 'A' && current <= 'Z') {
            maiusculas += 1;
        } 
        else if (current >= 'a' && current <= 'z') {
            minusculas += 1;
        } 
        else if (current >= '0' && current <= '9') {
            digitos += 1;
        }
        else if (current == ' ' || current == '\n' || current == '\t' || current == '\r') {
            espacos += 1;
        }
    }

    printf("Maiusculas: %d\n", maiusculas);
    printf("Minusculas: %d\n", minusculas);
    printf("Digitos: %d\n", digitos);
    printf("Espacos em branco: %d\n", espacos);

    fclose(file);
    return 0;
}