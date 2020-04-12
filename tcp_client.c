#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>

int main(void) {

	int client_fd; // file descriptor do socket do cliente

	int port = 22000;

	char *host = "127.0.0.1"; 

	char send_msg[100]; // string com mensagem a enviar
	char recv_msg[100]; // string com mensagem a receber

	struct sockaddr_in server_addr; // struct com informacoes do servidor a conectar

	client_fd = socket(AF_INET, SOCK_STREAM, 0); //criacao do socket cliente

	bzero(&server_addr, sizeof(server_addr)); // inicializacao da struct que armazenara endereco do servidor

	server_addr.sin_family = AF_INET; 
	server_addr.sin_port = htons(port); // associa porta do servidor a struct
	inet_aton(host, &server_addr.sin_addr); // associa endereco do servidor (armazenado na string host) a struct

	printf("Conectando-se a porta %d do servidor %s\n", port, host);

	connect(client_fd, (struct sockaddr*) &server_addr, sizeof(server_addr)); // funcao bloqueante, conecta ao servidor

	while(1) {
		bzero( send_msg, 100);
		bzero( recv_msg, 100);
		
		printf("Digite algo para enviar ao servidor: ");
		fgets(send_msg, 100, stdin); //le do usuario string para enviar ao servidor

		write(client_fd, send_msg, strlen(send_msg)+1);
		read(client_fd, recv_msg, 100); // le do servidor string para exibir para o usuario

		printf("Recebi do servidor: %s\n", recv_msg); // exibe o recebido na tela

	}	

	return 0;
}
