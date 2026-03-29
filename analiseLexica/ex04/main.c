#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *entrada = fopen("teste.c", "r");
    FILE *saida = fopen("clean.c", "w");

    if (entrada == NULL || saida == NULL) {
        printf("Erro fatal: Nao foi possivel abrir os arquivos.\n");
        return 1;
    }

    int estado = 0;
    int current;

    while ((current = fgetc(entrada)) != EOF) {
        
        switch (estado) {
            case 0: // Código Normal
                if (current == '/') {
                    estado = 1; // Liga o alerta: pode ser o início de um comentário
                } else {
                    fputc(current, saida); // Se não for barra, grava no arquivo novo normalmente
                }
                break;
                
            case 1: // Lemos uma '/' e estamos aguardando a confirmação
                if (current == '*') {
                    estado = 2; // Confirmado! Entramos no comentário /*
                } else if (current == '/') {
                    // Trata o caso raro de duas barras seguidas "//" que não são "/*"
                    fputc('/', saida); 
                    estado = 1;        
                } else {
                    // Alarme falso (ex: uma divisão matemática). 
                    fputc('/', saida); // Grava a barra que estava retida...
                    fputc(current, saida);   // ...e grava o caractere atual
                    estado = 0;        // Volta ao normal
                }
                break;
                
            case 2: // Buraco Negro (Dentro do comentário /* ... )
                if (current == '*') {
                    estado = 3; // Liga o alerta: pode ser o fim do comentário
                }
                // Se não for '*', não fazemos nada. O caractere é ignorado (apagado).
                break;
                
            case 3: // Lemos um '*' dentro do comentário ( ... * )
                if (current == '/') {
                    estado = 0; // Confirmado! Fechou o comentário */. Volta ao normal!
                } else if (current == '*') {
                    estado = 3; // Continua no alerta (trata casos de muitos asteriscos ex: /***/ )
                } else {
                    estado = 2; // Alarme falso. Volta pro buraco negro.
                }
                break;
        }
    }

    // Tratamento de segurança: se o arquivo acabar bem na hora que segurávamos uma barra solta
    if (estado == 1) {
        fputc('/', saida);
    }

    fclose(entrada);
    fclose(saida);

    printf("Deu bom.\n");

    return 0;
}