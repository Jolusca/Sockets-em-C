// Server.c - Servidor UDP que recebe mensagens e responde com o que for digitado
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>

#define PORTA 8888
#define TAM_BUFFER 512

int main() {
    WSADATA wsa;
    SOCKET servidor;
    struct sockaddr_in endereco_servidor, endereco_cliente;
    int tamanho_cliente = sizeof(endereco_cliente);
    char buffer_recebido[TAM_BUFFER];
    char buffer_envio[TAM_BUFFER];

    // Inicializando o Winsock
    WSAStartup(MAKEWORD(2,2), &wsa);

    // Criando o socket UDP
    servidor = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    // Configurando o endereço do servidor
    endereco_servidor.sin_family = AF_INET;
    endereco_servidor.sin_addr.s_addr = INADDR_ANY;
    endereco_servidor.sin_port = htons(PORTA);

    // Ligando (bind) o socket ao endereço e porta
    bind(servidor, (struct sockaddr*)&endereco_servidor, sizeof(endereco_servidor));

    printf("Servidor iniciado na porta %d\n", PORTA);

    while (1) {
        // Recebendo mensagem do cliente
        int recebido = recvfrom(servidor, buffer_recebido, TAM_BUFFER, 0,
                                (struct sockaddr*)&endereco_cliente, &tamanho_cliente);
        buffer_recebido[recebido] = '\0';

        printf("Mensagem recebida do cliente: %s\n", buffer_recebido);

        // Lendo mensagem de resposta no terminal
        printf("Digite a resposta: ");
        fgets(buffer_envio, TAM_BUFFER, stdin);
        buffer_envio[strcspn(buffer_envio, "\n")] = '\0'; // Tirando \n

        // Enviando de volta para o cliente
        sendto(servidor, buffer_envio, strlen(buffer_envio), 0,
               (struct sockaddr*)&endereco_cliente, tamanho_cliente);
    }

    closesocket(servidor);
    WSACleanup();
    return 0;
}
