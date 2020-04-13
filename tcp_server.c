#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <pthread.h>
#include <string.h>
#include <netinet/in.h>

typedef struct{
    int client_fd;
    char name[40];
}cliente;

void* responde_cliente(void* param);

char server_name[100];
cliente clientes[10];


int main(int argc, char ** argv) {

	char msg[140];
    int i = 0;
	int server_port = atoi(argv[1]);
    
    strcpy(server_name, argv[2]);

	int listen_fd; // dois file descriptors, 1 para ouvir solicitacoes, outro para o cliente
    
    
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
        
		clientes[i].client_fd = accept(listen_fd, (struct sockaddr*) NULL, NULL); // funcao bloqueante, gera novo socket
		pthread_create(&threads[thread_count++], NULL, (void*) responde_cliente, (void*) i++);
	}

	return 0;
}

void* responde_cliente(void* param) {

	int client_aux = clientes[(int) param].client_fd;
    int client_temp;
    
	char msg[100];
    char replica[200];
    int x = 0;
    
    read(client_aux, msg, 40);
    strcpy(clientes[(int) param].name, msg);
    printf("%s se conectou\n", clientes[(int)param].name);
    write(client_aux, server_name, strlen(server_name)+1);
    
    
	
	while(1) {
        
		bzero(msg, 100); // inicializa a mensagem com 0
        bzero(replica, 200);
        read(client_aux, msg, 140); // le mensagem do socket cliente associado
        printf("%s enviou uma mensagem: %s\n",  clientes[(int) param].name, msg); // exibe o que recebeu do cliente
        
        for(x = 0; x < 10; x++)
        {
            
            client_temp = clientes[x].client_fd;
            strcat(replica, clientes[x].name);
            strcat(replica, msg);
            write(client_temp, replica, strlen(msg)+1);
            bzero(replica, 200);
        }
    }
}
