//cliente Eco
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main() {
    int s;                    // socket do cliente
    char msg[100];            // buffer da mensagem
    struct sockaddr_in serv;  // endereço do servidor
    socklen_t servlen = sizeof(serv);  // tamanho do endereço do servidor

    s = socket(AF_INET, SOCK_DGRAM, 0);  // cria socket UDP

    memset(&serv, 0, sizeof(serv));     // limpa o endereço do servidor
    serv.sin_family = AF_INET;           // IPv4
    serv.sin_port = htons(8080);         // porta 8080
    serv.sin_addr.s_addr = 0x0100007F;   // IP 127.0.0.1 (localhost)

    while(1) {  // loop infinito, só para com Ctrl+C
        printf("Mensagem: ");
        fgets(msg, sizeof(msg), stdin);  // lê o que digitar

        msg[strcspn(msg, "\n")] = 0;    // tira o \n do fgets

        sendto(s, msg, strlen(msg), 0, (struct sockaddr *)&serv, servlen);  // manda mensagem pro servidor

        int n = recvfrom(s, msg, sizeof(msg) - 1, 0, (struct sockaddr *)&serv, &servlen);  // espera resposta
        msg[n] = '\0';  // finaliza a string

        printf("Resposta do servidor: %s\n", msg);  // mostra a resposta
    }

    close(s);  // fecha o socket (nunca chega aqui)
    return 0;
}
