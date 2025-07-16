//Servidor eco
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main() {
    int s;                      // socket que a gente vai usar
    char msg[100];              // buffer pra mensagem que chegar
    struct sockaddr_in serv;    // endereço do servidor
    struct sockaddr_in cli;     // endereço do cliente que mandou a mensagem
    socklen_t clilen = sizeof(cli);  // tamanho do endereço do cliente

    s = socket(AF_INET, SOCK_DGRAM, 0);  // cria o socket UDP

    memset(&serv, 0, sizeof(serv));  // limpa o endereço do servidor
    serv.sin_family = AF_INET;        // IPv4
    serv.sin_port = htons(8080);      // porta 8080
    serv.sin_addr.s_addr = 0;         // aceita mensagens de qualquer IP

    bind(s, (struct sockaddr *)&serv, sizeof(serv));  // associa o socket com o endereço

    printf("Servidor pronto, esperando mensagens...\n");

    while(1) {  // loop infinito pra ficar esperando mensagem
        int n = recvfrom(s, msg, sizeof(msg) - 1, 0, (struct sockaddr *)&cli, &clilen);
        msg[n] = '\0';  // finaliza a string

        printf("Mensagem do cliente: %s\n", msg);  // mostra o que chegou

        sendto(s, msg, n, 0, (struct sockaddr *)&cli, clilen);  // manda a mesma mensagem de volta
    }

    close(s);  // fecha o socket (nunca chega aqui porque é loop infinito)
    return 0;
}
