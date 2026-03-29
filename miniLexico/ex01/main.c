#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef enum {
    ERRO,
    IDENTIFICADOR,
    NUMERO,
    EOS,
    SOMA,
    ATRIBUICAO,
    IGUALDADE
} TAtomo;

typedef struct {
    TAtomo atomo;
    int linha;
    float atributo_numero;
    char atributo_ID[16]; // Limite de 15 caracteres + 1 para o '\0'
} TInfoAtomo;

FILE *arquivo_fonte;
int linha_atual = 1;

TInfoAtomo obter_atomo(void) {
    TInfoAtomo info_atomo;
    int estado = 0;
    char c;
    char buffer[100]; // Buffer para acumular lexemas
    int pos = 0;

    while (1) {
        c = fgetc(arquivo_fonte);

        // Trata o fim do arquivo no estado inicial
        if (c == EOF && estado == 0) {
            info_atomo.atomo = EOS;
            info_atomo.linha = linha_atual;
            return info_atomo;
        }

        switch (estado) {
            case 0:
                if (c == '\n') {
                    linha_atual++;
                } else if (c == ' ' || c == '\t' || c == '\r') {
                    estado = 0;
                } else if (c == '+') {
                    info_atomo.atomo = SOMA;
                    info_atomo.linha = linha_atual;
                    return info_atomo;
                } else if (c == '=') {
                    estado = 1;
                } else if (isalpha(c)) {
                    estado = 2; // Começou com letra: vai buscar Identificador
                    buffer[pos++] = c;
                } else if (isdigit(c)) {
                    estado = 3; // Começou com número: vai buscar a Constante
                    buffer[pos++] = c;
                } else if (c == EOF) {
                    info_atomo.atomo = EOS;
                    info_atomo.linha = linha_atual;
                    return info_atomo;
                } else {
                    info_atomo.atomo = ERRO;
                    info_atomo.linha = linha_atual;
                    return info_atomo;
                }
                break;

            case 1:
                if (c == '=') {
                    info_atomo.atomo = IGUALDADE;
                    info_atomo.linha = linha_atual;
                    return info_atomo;
                } else {
                    ungetc(c, arquivo_fonte);
                    info_atomo.atomo = ATRIBUICAO;
                    info_atomo.linha = linha_atual;
                    return info_atomo;
                }
                break;

            case 2: // Formando um IDENTIFICADOR
                // Permite letras e números no meio do nome da variável
                if (isalnum(c)) {
                    buffer[pos++] = c;
                    if (pos > 15) {
                        info_atomo.atomo = ERRO;
                        info_atomo.linha = linha_atual;
                        return info_atomo;
                    }
                } else {
                    ungetc(c, arquivo_fonte); // Retraimento
                    buffer[pos] = '\0'; // Finaliza a string
                    strcpy(info_atomo.atributo_ID, buffer); // Copia para o atributo
                    info_atomo.atomo = IDENTIFICADOR;
                    info_atomo.linha = linha_atual;
                    return info_atomo;
                }
                break;

            case 3: // Formando um NUMERO
                if (isdigit(c) || c == '.') {
                    buffer[pos++] = c;
                } else {
                    ungetc(c, arquivo_fonte); // Retraimento
                    buffer[pos] = '\0';
                    info_atomo.atributo_numero = atof(buffer); // Converte para float
                    info_atomo.atomo = NUMERO;
                    info_atomo.linha = linha_atual;
                    return info_atomo;
                }
                break;
        }
    }
}

int main() {
    TInfoAtomo token;
    
    arquivo_fonte = fopen("teste.txt", "r");
    if (arquivo_fonte == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    while (1) {
        token = obter_atomo();
        
        if (token.atomo == EOS) {
            break;
        }
        
        if (token.atomo == ERRO) {
            printf("Erro lexico na linha %d. Abortando a execucao.\n", token.linha);
            break; 
        }

        switch (token.atomo) {
            case SOMA:
                printf("%d# SOMA | -\n", token.linha);
                break;
            case ATRIBUICAO:
                printf("%d# ATRIBUICAO | -\n", token.linha);
                break;
            case IGUALDADE:
                printf("%d# IGUALDADE | -\n", token.linha);
                break;
            case IDENTIFICADOR:
                printf("%d# IDENTIFICADOR | %s\n", token.linha, token.atributo_ID);
                break;
            case NUMERO:
                printf("%d# NUMERO | %.2f\n", token.linha, token.atributo_numero);
                break;
            default:
                break;
        }
    }

    fclose(arquivo_fonte);
    return 0;
}