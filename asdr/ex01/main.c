#include <stdio.h>
#include <stdlib.h>

char fita[] = "+a*ba";
int pos = 0;
char token_atual;

void obter_atomo() {
    token_atual = fita[pos];
    if (token_atual != '\0') {
        pos++;
    }
}

void erro() {
    printf("Erro Sintatico encontrado!\n");
    exit(1);
}

void check(char esperado) {
    if (token_atual == esperado) {
        obter_atomo(); 
    } else {
        erro();
    }
}

void parseE() {
    if (token_atual == 'a') {
        check('a');
    } 
    else if (token_atual == 'b') {
        check('b');
    } 
    else if (token_atual == '+') {
        check('+');
        parseE(); // E
        parseE(); // E
    } 
    else if (token_atual == '*') {
        check('*');
        parseE(); // E
        parseE(); // E
    } 
    else {
        erro();
    }
}

int main() {
    printf("Iniciando analise da cadeia: %s\n", fita);
    
    obter_atomo(); // Lookahead inicial
    parseE();      // Símbolo inicial da gramática
    
    if (token_atual == '\0') {
        printf("Cadeia ACEITA com sucesso!\n");
    } else {
        printf("Erro Sintatico: lixo encontrado no final da cadeia.\n");
    }

    return 0;
}