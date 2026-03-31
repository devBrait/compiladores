#include <stdio.h>
#include <stdlib.h>

typedef enum {
    sINT,
    sFLOAT,
    sIDENT,
    sVIRGULA,
    EOS
} TToken;

// Simulando a fita de saída do Analisador Léxico (sINT seguido de sIDENT)
TToken fita[] = {sINT, sIDENT, EOS};
int pos = 0;
TToken token_atual;

void obter_atomo() {
    token_atual = fita[pos];
    if (token_atual != EOS) {
        pos++;
    }
}

void erro() {
    printf("Erro Sintatico encontrado!\n");
    exit(1);
}

void check(TToken esperado) {
    if (token_atual == esperado) {
        obter_atomo(); 
    } else {
        erro();
    }
}

// lstvar' → ',' sIDENT lstvar' | ε
void parseLstVarLinha() {
    if (token_atual == sVIRGULA) {
        check(sVIRGULA);
        check(sIDENT);
        parseLstVarLinha(); 
    }
}

// lstvar → sIDENT lstvar'
void parseLstVar() {
    check(sIDENT);
    parseLstVarLinha();
}

// decl → sINT lstvar | sFLOAT lstvar
void parseDecl() {
    if (token_atual == sINT) {
        check(sINT);
        parseLstVar();
    } else if (token_atual == sFLOAT) {
        check(sFLOAT);
        parseLstVar();
    } else {
        erro();
    }
}

int main() {
    obter_atomo(); // Lookahead inicial
    parseDecl();   // Símbolo inicial da gramática
    
    if (token_atual == EOS) {
        printf("Comando de declaracao ACEITO com sucesso!\n");
    } else {
        printf("Erro Sintatico: caracteres inesperados no final da linha.\n");
    }

    return 0;
}