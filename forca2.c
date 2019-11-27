#include <stdio.h>
#include <string.h>
void lerArquivo();
char palavra[256];

void lerArquivo(){
    FILE *p;
    p = fopen("segredo.txt", "r");
    if(p == NULL)
        printf("nao foi possivel abrir o arquivo\n");
    else
        fscanf(p, " %[^\n]", palavra);
    fclose(p);
    printf("%s", palavra);
}

int main(){
    lerArquivo();
    return 0;

}