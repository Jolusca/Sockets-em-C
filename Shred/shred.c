#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    // Abre o arquivo no modo leitura/escrita binária
    FILE *arquivo = fopen("Deletar.txt", "r+b");
    
    // Descobrir seu tamanho
    fseek(arquivo, 0, SEEK_END);
    long tamanho = ftell(arquivo);
    // Volta para o início do arquivo para começar a sobrescrever
    fseek(arquivo, 0, SEEK_SET);

    // Variável zero que será escrita em cada byte
    unsigned char zero = 0;
    // Loop para escrever byte a byte
    for (long i = 0; i < tamanho; i++) {
        fwrite(&zero, 1, 1, arquivo);
    }
    // Fecha o arquivo
    fclose(arquivo);
    // Mensagem de sucesso
    printf("Arquivo sobrescrito com zeros com sucesso!\n");
    // Retorna 0 indicando execução bem-sucedida
    return 0;
}