// Client.c - Cliente UDP que envia mensagem e recebe resposta
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>

#define IP_SERVIDOR "127.0.0.1"
#define PORTA 8888
#define TAM_BUFFER 512

int main() {
    WSADATA wsa;
    SOCKET cliente;
    struct sockaddr_in endereco_servidor;
    int tamanho = sizeof(endereco_servidor);
    char mensagem[TAM_BUFFER];
    char resposta[TAM_BUFFER];

    // Inicializando o Winsock
    WSAStartup(MAKEWORD(2,2), &wsa);

    // Criando o socket UDP
    cliente = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    // Configurando o endereço do servidor
    endereco_servidor.sin_family = AF_INET;
    endereco_servidor.sin_port = htons(PORTA);
    endereco_servidor.sin_addr.s_addr = inet_addr(IP_SERVIDOR);

    while (1) {
        // Lendo mensagem a ser enviada
        printf("Digite uma mensagem para o servidor: ");
        fgets(mensagem, TAM_BUFFER, stdin);
        mensagem[strcspn(mensagem, "\n")] = '\0';

        // Enviando ao servidor
        sendto(cliente, mensagem, strlen(mensagem), 0,
               (struct sockaddr*)&endereco_servidor, tamanho);

        // Recebendo resposta
        int recebido = recvfrom(cliente, resposta, TAM_BUFFER, 0,
                                (struct sockaddr*)&endereco_servidor, &tamanho);
        resposta[recebido] = '\0';
        printf("Resposta do servidor: %s\n\n", resposta);
    }

    closesocket(cliente);
    WSACleanup();
    return 0;
}
