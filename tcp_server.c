#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <pthread.h>
#include <string.h>

void* responde_cliente(void* param);

char server_name[100];


int main(int argc, char ** argv) {

	char msg[140];

	int server_port = atoi(argv[1]);
    
    strcpy(server_name, argv[2]);

	int listen_fd, client_fd; // dois file descriptors, 1 para ouvir solicitacoes, outro para o cliente

	struct sockaddr_in server_addr; // struct com informacoes para o server socket
	struct sockaddr_in client_addr; // struct que armazenara informacoes do cliente conectado

	pthread_t threads[10]; // array que armazenara 10 threads (MAXIMO DE CLIENTES)
 
	int thread_count = 0; // contador de threads (de clientes)

	printf("Loading...\n");

	listen_fd = socket(AF_INET, SOCK_STREAM, 0); // listen_fd representa o socket que aguardara requisicoes

	bzero(&server_addr, sizeof(server_addr)); // Inicializa a estrutura do servidor sockaddr_in com 0
	bzero(&client_addr, sizeof(client_addr)); // Inicializa a estrutura do cliente sockaddr_in com 0

	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY; // Constante sinaliza que o socket sera um servidor
	server_addr.sin_port = htons(server_port); // Porta a ser associada ao socket servidor criado

	bind(listen_fd, (struct sockaddr*) &server_addr, sizeof(server_addr)); // associa parametros definidos

	listen(listen_fd, 10); // sinaliza que aguardara conexoes na porta associada

	printf("Inicilizando bate-papo %s na porta %d...\n", server_name, server_port);

	while (1) {
		client_fd = accept(listen_fd, (struct sockaddr*) NULL, NULL); // funcao bloqueante, gera novo socket 
		pthread_create(&threads[thread_count++], NULL, (void*) responde_cliente, (void*) client_fd);
	}

	return 0;
}

void* responde_cliente(void* param) {

	int client_fd = (int) param;

	char msg[140];
    
    char client_name[40];
    read(client_fd, msg, 40);
    printf("
    write(client_fd, server_name, strlen(server_name)+1);
    
	
	while(1) {
		bzero(msg, 140); // inicializa a mensagem com 0
        read(client_fd, msg, 140); // le mensagem do socket cliente associado
        printf("%s\n",msg); // exibe o que recebeu do cliente
        write(client_fd, msg, strlen(msg)+1); // envia de volta a mesma mensgem
        
	}
}
