#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef enum {
    ERRO,
    sIDENTIF,
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
    char atributo_ID[16]; 
} TInfoAtomo;

FILE *arquivo_fonte;
int linha_atual = 1;

TInfoAtomo obter_atomo(void) {
    TInfoAtomo info_atomo;
    int estado = 0;
    char c;
    char buffer[100]; 
    int pos = 0;

    while (1) {
        c = fgetc(arquivo_fonte);

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
                } else if (islower(c)) { 
                    // Regra: [a-z] (Obrigatoriamente letra minúscula no início)
                    estado = 2; 
                    buffer[pos++] = c;
                } else if (isdigit(c)) {
                    estado = 3; 
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

            case 2: // Regra: [A-Za-z0-9]*
                if (isalnum(c)) {
                    buffer[pos++] = c;
                    if (pos > 15) {
                        info_atomo.atomo = ERRO;
                        info_atomo.linha = linha_atual;
                        return info_atomo;
                    }
                } else if (c == '_') {
                    // Encontrou o '_' obrigatório. Vai para a validação final.
                    estado = 4;
                    buffer[pos++] = c;
                    if (pos > 15) {
                        info_atomo.atomo = ERRO;
                        info_atomo.linha = linha_atual;
                        return info_atomo;
                    }
                } else {
                    // Erro: O lexema terminou, mas não teve o '_' obrigatório.
                    info_atomo.atomo = ERRO;
                    info_atomo.linha = linha_atual;
                    return info_atomo;
                }
                break;

            case 3: // Lógica inalterada para NUMERO
                if (isdigit(c) || c == '.') {
                    buffer[pos++] = c;
                } else {
                    ungetc(c, arquivo_fonte); 
                    buffer[pos] = '\0';
                    info_atomo.atributo_numero = atof(buffer); 
                    info_atomo.atomo = NUMERO;
                    info_atomo.linha = linha_atual;
                    return info_atomo;
                }
                break;

            case 4: // Regra após o '_': ([0-9]+ | \epsilon)
                if (isdigit(c)) {
                    // Entrou na opção de ter dígitos no final ([0-9]+)
                    estado = 5;
                    buffer[pos++] = c;
                    if (pos > 15) {
                        info_atomo.atomo = ERRO;
                        info_atomo.linha = linha_atual;
                        return info_atomo;
                    }
                } else {
                    // Entrou na opção Epsilon (\epsilon): Terminou logo após o '_'
                    ungetc(c, arquivo_fonte); // Devolve o caractere que não faz parte
                    buffer[pos] = '\0'; 
                    strcpy(info_atomo.atributo_ID, buffer); 
                    info_atomo.atomo = sIDENTIF;
                    info_atomo.linha = linha_atual;
                    return info_atomo;
                }
                break;

            case 5: // Regra consumindo o restante dos dígitos ([0-9]+)
                if (isdigit(c)) {
                    buffer[pos++] = c;
                    if (pos > 15) {
                        info_atomo.atomo = ERRO;
                        info_atomo.linha = linha_atual;
                        return info_atomo;
                    }
                } else {
                    // Finalizou a sequência de dígitos
                    ungetc(c, arquivo_fonte); 
                    buffer[pos] = '\0'; 
                    strcpy(info_atomo.atributo_ID, buffer); 
                    info_atomo.atomo = sIDENTIF;
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
            case sIDENTIF:
                printf("%d# sIDENTIF | %s\n", token.linha, token.atributo_ID);
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