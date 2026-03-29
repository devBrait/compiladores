#include <stdio.h>

int main(){

    FILE *file = fopen("ex7.txt", "r");

    int quantLines = 1;
    int count = 0;

    if (file == NULL){
        printf("Erro na importação do file");
        return 1;
    }

    while ((count = fgetc(file)) != EOF)
        if (count == '\n') quantLines += 1;

    printf("%d\n", quantLines);
    fclose(file);

    return 0;
}