/* 
    File: simpleclient.C

    Author: R. Bettati
            Department of Computer Science
            Texas A&M University
    Date  : 2013/01/31

    Simple client main program for MP3 in CSCE 313
*/

/*--------------------------------------------------------------------------*/
/* DEFINES */
/*--------------------------------------------------------------------------*/

    /* -- (none) -- */

/*--------------------------------------------------------------------------*/
/* INCLUDES */
/*--------------------------------------------------------------------------*/

#include <cassert>
#include <cstring>
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

#include <errno.h>
#include <unistd.h>
#include <vector>

#include "client.H"
#include "reqchannel.H"

using namespace std;

const string QUIT_SIGIL = "MAGIC_QUIT_SIGIL_BETTATTI_IS_THE_BEST_PROF";

Semaphore mutex_l(1);
int worker_threads = 1;
int request_threads = 0;
int request_count = 100;
BoundedBuffer* request_buffer;
BoundedBuffer* response_buffer;

int main(int argc, char * argv[]) {
	if (!fork()) {
		system("./dataserver");
		return 0;
	}

	int buffer_size = 2000;
	
	char c;
	while ((c = getopt (argc, argv, "n:b:w:")) != -1) {
		switch (c) {
		case 'n':
			request_count = atoi(optarg);
			break;
		case 'b':
			buffer_size = atoi(optarg);
			break;
		case 'w':
			worker_threads = atoi(optarg);
			break;
		case '?':
			if (optopt == 'n' || optopt == 'b' || optopt == 'w') {
				printf("Option -%c requires an argument\n", optopt);
			} else {
				printf("Unknown option: -%c\n", optopt);
			}
		default:
			return -1;
		}
	}
	
	cout << "Main: CLIENT STARTED:" << endl;

	cout << "Main: Establishing control channel... " << flush;
	RequestChannel chan("control", RequestChannel::CLIENT_SIDE);
	cout << "done." << endl;;

	string hello_reply = chan.send_request("hello");
	cout << "Main: (control) 'hello' -> '" << hello_reply << "'" << endl;
	request_buffer = new BoundedBuffer(buffer_size);
	response_buffer = new BoundedBuffer(buffer_size);
	
	vector<string> names = {"Joe Smith", "Jane Smith", "John Doe"};
	
	request_threads = names.size();

	vector<pthread_t> threads(names.size()*2 + worker_threads);
	
	for (int i = 0; i < names.size(); ++i) {
		pthread_t request_id = threads.at(i*2);
		pthread_create(&request_id, NULL, request_thread, (void*)new string(names[i]));
		threads[i*2] = request_id;
		
		pthread_t stat_id = threads.at(i*2 + 1);
		pthread_create(&stat_id, NULL, stat_thread, (void*)new string(names[i]));
		threads[i*2+1] = request_id;
	}
	
	for (int i = 0; i < worker_threads; ++i) {
		string chan_name = chan.send_request("newthread");
		mutex_l.P();
		cout << "Main: (control) 'newthread' -> '" << chan_name << "'" << endl;
		mutex_l.V();

		pthread_t worker_id = threads.at(names.size()*2 + i);
		pthread_create(&worker_id, NULL, worker_thread, (void*)new string(chan_name));
		threads[names.size()*2 + i] = worker_id;
	}

	for (pthread_t thread : threads) {
		pthread_join(thread, NULL);
	}
	
	string quit_reply = chan.send_request("quit");
	cout << "Main: (control) 'quit' -> '" << quit_reply << "'" << endl;
	
	wait(NULL);
}

void * request_thread(void * _attr) {
	string* name = (string*)_attr;
	for (int i = 0; i < request_count; ++i) {
		string request_string = "data " + *name;
		mutex_l.P();
		cout << "Request: (" << *name << ") " << request_string << endl;
		mutex_l.V();
		request_buffer->push(request_string);
	}
	if (--request_threads == 0) {
		request_buffer->push(QUIT_SIGIL);
	}
	delete name;
	pthread_exit(0);
	return 0;
}

void * worker_thread(void * _attr) {
	string* chan_name = (string*)_attr;
	RequestChannel* chan = new RequestChannel(*chan_name, RequestChannel::CLIENT_SIDE);

	for (;;) {
		string request_string = request_buffer->pop();
		if (request_string == QUIT_SIGIL) {
			break;
		}
		string reply_string = chan->send_request(request_string);
		mutex_l.P();
		cout << "Worker:  (" << *chan_name << ") '" << request_string << "' -> '" << reply_string << "'" << endl;
		mutex_l.V();
		response_buffer->push(reply_string);
	}
	request_buffer->push(QUIT_SIGIL);
	if (--worker_threads == 0) {
		response_buffer->push(QUIT_SIGIL);
	}
	string quit_response = chan->send_request("quit");
	mutex_l.P();
	cout << "Worker:  (" << *chan_name << ") 'quit' -> '" << quit_response << "'" << endl;
	mutex_l.V();
	delete chan_name;
	pthread_exit(0);
	return 0;
}

void * stat_thread(void * _attr) {
	string* name = (string*)_attr;

	for (;;) {
		string response_string = response_buffer->pop();
		if (response_string == QUIT_SIGIL) {
			break;
		}
		mutex_l.P();
		cout << "Stat:    (" << *name << ") " << response_string << endl;
		mutex_l.V();
	}
	response_buffer->push(QUIT_SIGIL);
	delete name;
	pthread_exit(0);
	return 0;
}
