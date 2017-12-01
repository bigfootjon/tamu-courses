#ifndef _netreqchannel_H_
#define _netreqchannel_H_

#include <string>

using namespace std;

class NetworkRequestChannel {
private:
	int sock = 0;
	const int MAX_MESSAGE = 255;
public:
	// Client
	NetworkRequestChannel(const string _server_host_name, const unsigned short _port_no);
	// Server
	NetworkRequestChannel(const unsigned short _port_no, void * (*connection_handler) (int *));
	~NetworkRequestChannel();
	string send_request(string _request);
	string cread();
	int cwrite(string _msg);
	
};

#endif
