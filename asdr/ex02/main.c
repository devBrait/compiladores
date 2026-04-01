#include <stdio.h>
#include <stdlib.h>

typedef enum {
    sA_CHAR,   // 'a'
    sB_CHAR,   // 'b'
    sC_CHAR,   // 'c'
    sD_CHAR,   // 'd'
    sE_CHAR,   // 'e'
    EOS
} TToken;

// bcabcbb → b c a b c b b
TToken fita[] = {sB_CHAR, sC_CHAR, sA_CHAR, sB_CHAR, sC_CHAR, sB_CHAR, sB_CHAR, EOS};
int pos = 0;
TToken token_atual;

void parseA();
void parseB();
void parseC();
void parseD();

void obter_atomo() {
    token_atual = fita[pos];
    if (token_atual != EOS) pos++;
}

void erro() {
    printf("Erro Sintatico encontrado!\n");
    exit(1);
}

void check(TToken esperado) {
    if (token_atual == esperado) obter_atomo();
    else erro();
}

// D → da
void parseD() {
    check(sD_CHAR);
    check(sA_CHAR);
}

// C → aA | ε   (ε quando lookahead = 'b' ∈ FOLLOW(C))
void parseC() {
    if      (token_atual == sA_CHAR) { check(sA_CHAR); parseA(); }
    else if (token_atual == sB_CHAR) return;  // C → ε
    else erro();
}

// B → cC | eD
void parseB() {
    if      (token_atual == sC_CHAR) { check(sC_CHAR); parseC(); }
    else if (token_atual == sE_CHAR) { check(sE_CHAR); parseD(); }
    else erro();
}

// A → bBb
void parseA() {
    check(sB_CHAR);
    parseB();
    check(sB_CHAR);
}

int main() {
    obter_atomo();  // lookahead inicial
    parseA();       // símbolo inicial da gramática

    if (token_atual == EOS)
        printf("Cadeia ACEITA com sucesso!\n");
    else
        printf("Erro Sintatico: caracteres inesperados no final.\n");

    return 0;
}