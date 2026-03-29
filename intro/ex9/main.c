#include <stdio.h>
#include <string.h>

// Vetor com as principais palavras reservadas da linguagem C
const char *dic_keyword[] = {
    "int", "return", "if", "else", "while", "for", "do", "break", 
    "continue", "void", "char", "float", "double", "struct", 
    "switch", "case", "default", "sizeof", NULL // NULL marca o fim da lista
};

// Função auxiliar que verifica se uma palavra está na lista de reservadas
int isKeyword(char *palavra) {
    for (int i = 0; dic_keyword[i] != NULL; i++) {
        if (strcmp(palavra, dic_keyword[i]) == 0) {
            return 1; // Verdadeiro, é reservada
        }
    }
    return 0;
}

int main() {
    FILE *file = fopen("ex9.txt", "r");
    
    if (file == NULL) {
        printf("Erro na importacao do file\n");
        return 1;
    }

    int current;
    char lexema[256]; // Buffer para acumular a palavra (lexema)
    int index = 0;   // Controla a posição atual dentro do buffer

    while ((current = fgetc(file)) != EOF) {
        // Verifica se o caractere é letra minúscula, maiúscula ou número/underline
        if ((current >= 'a' && current <= 'z') || 
            (current >= 'A' && current <= 'Z') || 
            (current >= '0' && current <= '9') || 
            current == '_') {
            
            // Faz parte de uma palavra, então guardamos no buffer
            if (index < 255) {
                lexema[index] = current;
                index++;
            }
        } else {
            // Encontramos um delimitador (espaço, \n, (, ;, etc.)
            // Isso significa que a palavra atual terminou.
            if (index > 0) {
                lexema[index] = '\0'; // Finaliza a string do lexema com nulo
                
                if (isKeyword(lexema)) {
                    // Se for reservada, imprime convertendo letra por letra para maiúsculo
                    for (int i = 0; lexema[i] != '\0'; i++) {
                        if (lexema[i] >= 'a' && lexema[i] <= 'z') {
                            printf("%c", lexema[i] - 32); // -32 na tabela ASCII converte para maiúsculo
                        } else {
                            printf("%c", lexema[i]);
                        }
                    }
                } else {
                    // Se não for reservada (ex: nome de variável), imprime normal
                    printf("%s", lexema);
                }
                
                index = 0; // Zera o índice para começar a ler a próxima palavra
            }
            
            // Imprime o delimitador atual que fez a palavra fechar (o espaço, o ponto, etc.)
            printf("%c", current);
        }
    }

    // Caso o arquivo termine com uma palavra sem espaço ou quebra de linha no final
    if (index > 0) {
        lexema[index] = '\0';
        if (isKeyword(lexema)) {
            for (int i = 0; lexema[i] != '\0'; i++) {
                if (lexema[i] >= 'a' && lexema[i] <= 'z') {
                    printf("%c", lexema[i] - 32);
                } else {
                    printf("%c", lexema[i]);
                }
            }
        } else {
            printf("%s", lexema);
        }
    }

    fclose(file);
    return 0;
}