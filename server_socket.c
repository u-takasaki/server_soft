#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>

void format_port16(uint16_t net_order_port, char *sbuf, size_t sbuf_size);
void format_port32(uint32_t net_order_port, char *sbuf, size_t sbuf_size);
int server_socket(const char *node, const char *servicem,
									char hbuf, size_t hbuf_size,
									char sbuf, size_t sbuf_size);
void recv_loop(int client_fd, char *string, size_t str_size);
void accept_loop(int soc);

int main(int argc, char *argv[], char *envp[])
{

}

void format_port16(uint16_t net_order_port, char *sbuf, size_t sbuf_size)
{
	uint16_t port = ntohs(net_order_port);
	int len = snprintf(sbuf, NI_MAXSERV, "%u", port);
	if(len < 0 || len >= sbuf_size){
		/*failed to store or buffer ober fllow*/
		fprintf(stderr, "snprintf failed or truncated\r\n");
		sbuf[0] = '\0';
	}
}

void format_port32(uint32_t net_order_port, char *sbuf, size_t sbuf_size)
{
	uint32_t port = ntohl(net_order_port);
	int len = snprintf(sbuf, NI_MAXSERV, "%u", port);
	if(len < 0 || len >= sbuf_size){
		fprintf(stderr, "snprintf failed or truncated\r\n");
		sbuf[0] = '\0';
	}
}

int server_socket(const char *node, const char *service,
									char hbuf, size_t hbuf_size,
									char sbuf, size_t sbuf_size)
{
	struct sockaddr_storage ss;
	socklen_t ss_len = sizeof(ss);
	struct addrinfo hints, *res, *tmp;
	int errcode, soc, opt;

	/*clear addrinfo hints by zero*/
	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_flags = AI_PASSIVE;
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;

	if((errcode = getaddrinfo(node, service, &hints, &res)) != 0){
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(errcode));
		return -1;
	}
	fprintf(stdout, "listen NIC and Port are....\r\n");
	tmp = res;
	opt = 1;
	while(tmp){
		if((soc = socket(tmp->ai_family, tmp->ai_socktype, 0)) < 0){
			perror("socket");
			freeaddrinfo(res);
			return -1;
		}
		if(setsockopt(soc, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) != 0){
			perror("setsockopt");
			freeaddrinfo(res);
			return -1;
		}
		#ifdef SO_REUSEPORT
		if(setsockopt(soc, SOL_SOCKET, SO_REUSEPORT, &opt, sizeof(opt)) != 0){
			perror("setsockopt");
			freeaddrinfo(res);
			return -1;
		}
		#endif
		if(bind(soc, sock->ai_addr, sock->ai_addrlen) == 0){
			break;
		}
		tmp = tmp->ai_next;
		close(soc);
	}
		
	if(tmp == NULL){
		fprintf(stderr, "failed to bind server socket\r\n");
		return -1;
	}

	freeaddrinfo(res);

	if(listen(soc, SOMAXCONN) < 0){
		perror("listen");
		return -1;
	}

	if(getsockname(soc, (struct sockaddr*)&ss, &ss_len) == -1){
		perror("getsockname");
	}

	if(ss.ss_family == AF_INET){
		struct sockaddr_in *s_ipv4 = (struct sockaddr_in *)&ss;
		if(inet_ntop(AF_INET, &s_ipv4, hbuf, hbuf_size) == NULL){
			perror("inet_ntop");
		}
		format_port16(s_ipv4->sin_port, sbuf);
	} else if(ss.ss_family == AF_INET6){
		struct sockaddr_in6 *s_ipv6 = (struct sockaddr_in *)&ss;
		if(inet_ntop(AF_INET6, &s_ipv6, hbuf, hbuf_size) == NULL){
			perror("inet_ntop");
		}
		format_port16(s_ipv6->sin6_port, sbuf);
	}

	return soc;
}

void recv_loop(int client_fd, char *string, size_t str_size)
{
	for(;;){
		int n = recv(client_fd, string, str_size, 0);
		if(n == 0){
			close(client_fd);
			break;
		} else if(n > str_size){
			fprintf(st

void accept_loop(int soc)
{
	int client_fd;
	struct sockaddr_storage client_addr;
	socklen_t addrlen = sizeof(client_addr);

	for(;;){
		client_fd = accept(soc, (struct sockaddr *)&client_addr, &addrlen)
		if(client_fd < 0){
			perror("accept");
			continue;
		} else{

		}
		close(client_fd);
		client_fd = 0;
	}
	
}
