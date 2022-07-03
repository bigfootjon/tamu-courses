#include "netreqchannel.H"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <errno.h>
#include <netdb.h>

// Client
NetworkRequestChannel::NetworkRequestChannel(const string _server_host_name, const unsigned short _port_no) {
	hostent *host = gethostbyname(_server_host_name.c_str());
	if (host == NULL || host->h_addr_list[0] == NULL) {
		printf("Server host '%s' lookup failed!\n", _server_host_name.c_str());
		exit(1);
	}
	sockaddr_in sin;
	sin.sin_family = AF_INET;
	sin.sin_port = htons(_port_no);
	sin.sin_addr = *(in_addr*)(host->h_addr_list[0]);
	
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0) {
		printf("can't create socket: %s\n", strerror(errno));
		exit(1);
	}
	if (connect(sock, (struct sockaddr *)&sin, sizeof(sin)) < 0) {
		printf("can't connect to %s:%d: %s", _server_host_name.c_str(), _port_no, strerror(errno));
	}
}

// Server
NetworkRequestChannel::NetworkRequestChannel(const unsigned short _port_no, int backlog, void * (*connection_handler) (int *)) {
	int m_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (m_sock < 0) printf("can't create socket: %s\n", strerror(errno));
	sockaddr_in sin;
	memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = INADDR_ANY;
	sin.sin_port = htons(_port_no);
	if (bind(m_sock, (struct sockaddr *)&sin, sizeof(sin)) < 0) {
		printf("can't bind\n");
	}
	if (listen(m_sock, backlog) < 0) {
		printf("can't listen\n");
	}
	for (;;) {
		struct sockaddr cin;
		socklen_t cin_size = sizeof(cin);
		int s_sock = accept(m_sock, &cin, &cin_size);
		if (connection_handler != NULL) {
			connection_handler(&s_sock);
		} else {
			close(s_sock);
		}
	}
}

// Server Slave
NetworkRequestChannel::NetworkRequestChannel(int fd) {
	sock = fd;
}

NetworkRequestChannel::~NetworkRequestChannel() {
	if (sock > 0) {
		close(sock);
	}
}

string NetworkRequestChannel::send_request(string _request) {
	cwrite(_request);
	string s = cread();
	return s;
}

string NetworkRequestChannel::cread() {
	if (sock <= 0) {
		printf("can't cread in server mode\n");
		return "";
	}
	char buf[MAX_MESSAGE];
	if (read(sock, buf, MAX_MESSAGE) < 0) {
		perror(string("Request Channel: Error reading from pipe!").c_str());
	}
	string s = buf;
	return s;
}

int NetworkRequestChannel::cwrite(string _msg) {
	if (sock <= 0) {
		printf("can't cwrite in server mode\n");
		return -1;
	}
	if (_msg.length() >= MAX_MESSAGE) {
		perror(string("Message too long for Channel!").c_str());
		return -1;
	}
	const char * s = _msg.c_str();
	if (write(sock, s, strlen(s)+1) < 0) {
		perror(string("Request Channel: Error writing to pipe!").c_str());
	}
	return 0;
}
