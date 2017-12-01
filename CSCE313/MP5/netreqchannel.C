#include "netreqchannel.H"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

// Client
NetworkRequestChannel::NetworkRequestChannel(const string _server_host_name, const unsigned short _port_no) {
	sockaddr_in sin;
	sin.sin_family = AF_INET;
	sin.sin_port = htons(_port_no);
	inet_aton(_server_host_name.c_str(), &sin.sin_addr);
	
	sock = socket(AF_INET, SOCK_STREAM, 0);	
	connect(sock, (struct sockaddr *)&sin, sizeof(sin));
}

// Server
NetworkRequestChannel::NetworkRequestChannel(const unsigned short _port_no, void * (*connection_handler) (int *)) {

}

// Descructor
NetworkRequestChannel::~NetworkRequestChannel() {
}

string NetworkRequestChannel::send_request(string _request) {
	cwrite(_request);
	string s = cread();
	return s;
}

string NetworkRequestChannel::cread() {
	char buf[MAX_MESSAGE];
	if (read(sock, buf, MAX_MESSAGE) < 0) {
		perror(string("Request Channel: Error reading from pipe!").c_str());
	}
	string s = buf;
	return s;
}

int NetworkRequestChannel::cwrite(string _msg) {
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
