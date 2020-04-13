#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>

int main(int argc, char** argv) {

	int client_fd; // file descriptor do socket do cliente

	int port = atoi(argv[2]);
	
	int client_name[40];
    
    strcpy(client_name, argv[3]);

	char *host = argv[1];

	char msg[100]; // msg digitada pelo cliente
	char send_msg[140]; // msg do cliente junto com o nome para envio
	char recv_msg[100]; // string com mensagem a recebe

	struct sockaddr_in server_addr; // struct com informacoes do servidor a conectar

	client_fd = socket(AF_INET, SOCK_STREAM, 0); //criacao do socket cliente

	bzero(&server_addr, sizeof(server_addr)); // inicializacao da struct que armazenara endereco do servidor

	server_addr.sin_family = AF_INET; 
	server_addr.sin_port = htons(port); // associa porta do servidor a struct
	inet_aton(host, &server_addr.sin_addr); // associa endereco do servidor (armazenado na string host) a struct

	printf("Conectando-se ao servidor %s na porta %d\n", host, port);

	connect(client_fd, (struct sockaddr*) &server_addr, sizeof(server_addr)); // funcao bloqueante, conecta ao servidor
    
    bzero( send_msg, 140);
    bzero( recv_msg, 100);
    strcat(send_msg, client_name);
    write(client_fd, send_msg, strlen(send_msg)+1);
    printf("Apelido: %s\n", client_name);
    read(client_fd, recv_msg, 140);
    printf("Mensagem do servidor: %s\n", recv_msg);

	while(1) {
		bzero( send_msg, 140);
		bzero( recv_msg, 100);
		
		printf("Digite sua mensagem: ");
		fgets(msg, 100, stdin); //le do usuario string para enviar ao servidor
        strcat(send_msg, client_name);
        strcat(send_msg, ": ");
        strcat(send_msg, msg);
		write(client_fd, send_msg, strlen(send_msg)+1);
        
		read(client_fd, recv_msg, 140); // le do servidor string para exibir para o usuario
		printf("%s\n", recv_msg); // exibe o recebido na tela

	}	

	return 0;
}
