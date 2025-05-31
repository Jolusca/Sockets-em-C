# Sockets UDP em C (Cliente/Servidor)
## Arquivos

- `Server.c`: roda o servidor que recebe mensagem do cliente e responde com o que você digitar.
- `Client.c`: envia uma mensagem para o servidor e mostra a resposta.


```bash
gcc Server.c -o servidor.exe -lws2_32
gcc Client.c -o cliente.exe -lws2_32
