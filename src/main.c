#include <stdio.h>

#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/net/net_ip.h>
#include <zephyr/net/socket.h>

#include <zephyr/console/console.h>

LOG_MODULE_REGISTER(main, CONFIG_APP_LOG_LEVEL);

#define HOKUYO_PORT 10940
#define BUFFER_SIZE 64+2+6

int main(void)
{
	printf("\nStarting connection\n");
	struct sockaddr_in addr4;
	addr4.sin_family = AF_INET;
	addr4.sin_port = htons(HOKUYO_PORT);
	inet_pton(AF_INET, CONFIG_NET_CONFIG_PEER_IPV4_ADDR,
			  &addr4.sin_addr);

	int client_soc = socket(AF_INET, SOCK_STREAM, 0);

	if (client_soc < 0){
		printf("\nFailed to init socket\n");
		return -1;
	}

	int ret = connect(client_soc, (struct sockaddr *)&addr4, sizeof(addr4));
	if (ret < 0){
		printf("\nfailed to connect\n");
		return -1;
	}

	console_init();

	while (1) {
		uint8_t c = console_getchar();

		if (c == 0x71){
			break;
		}
		// if (c == 0x31){
		// 	char buffer[BUFFER_SIZE];
		// 	char* message = "SCIP2.0\n";
		// 	if (send(client_soc, message, strlen(message), MSG_TRUNC) != (int)strlen(message)){
		// 		printf("\nfailed to send message\n");
		// 		return -1;
		// 	}
		// 	recv(client_soc, buffer,BUFFER_SIZE, MSG_DONTWAIT);
		// 	printf("Result is: %s\n", buffer);
		// }
		if (c == 0x32){
			char buffer[BUFFER_SIZE];
			char* message = "VV\n";
			if (send(client_soc, message, strlen(message), MSG_TRUNC) != (int)strlen(message)){
				printf("\nfailed to send message\n");
				return -1;
			}
			for (int i = 0; i < BUFFER_SIZE; ++i){
				recv(client_soc, buffer,BUFFER_SIZE, MSG_DONTWAIT);
			}
			printf("Result is: %s\n", buffer);
		}
		if (c == 0x33){
			char buffer[BUFFER_SIZE];
			char* message = "BM\n";
			if (send(client_soc, message, strlen(message), MSG_TRUNC) != (int)strlen(message)){
				printf("\nfailed to send message\n");
				return -1;
			}
			for (int i = 0; i < BUFFER_SIZE; ++i){
				recv(client_soc, buffer,BUFFER_SIZE, MSG_DONTWAIT);
			}
			printf("Result is: %s\n", buffer);
			printbuffer(buffer);
		}
		if (c == 0x34){
			char buffer[BUFFER_SIZE];
			char* message = "GS0044072501\n";
			if (send(client_soc, message, strlen(message), MSG_TRUNC) != (int)strlen(message)){
				printf("\nfailed to send message\n");
				return -1;
			}
			for (int i = 0; i < BUFFER_SIZE; ++i){
				recv(client_soc, buffer,BUFFER_SIZE, MSG_DONTWAIT);
			}
			printf("Result is: %s\n", buffer);
		}
		printk("char: [0x%x] %c\n", c, c);
	}

	// for (int i = 0; i < BUFFER_SIZE; ++i){
	// 	recv(client_soc, buffer,BUFFER_SIZE, MSG_DONTWAIT);
	// }



	close(client_soc);

	printf("\nSuccess!\n");
	return 0;
}

void printbuffer(char buffer[]){
	for (int i = 0; i < BUFFER_SIZE; i++){
		if (buffer[i] != NULL){
			//printf("hex: %x\n", buffer[i]);
			printbinchar(buffer[i]);
		}
	}
}

void printbinchar(char character)
{
    char output[9];
    itoa(character, output, 2);
    printf("binary: %s\n", output);
}

