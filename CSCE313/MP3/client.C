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

#include <errno.h>
#include <unistd.h>
#include <vector>

#include "client.H"
#include "reqchannel.H"

using namespace std;

const string QUIT_SIGIL = "MAGIC_QUIT_SIGIL_BETTATTI_IS_THE_BEST_PROF";
Semaphore mutex_l(1);

int main(int argc, char * argv[]) {
	int request_count = 100;
	int buffer_size = 2000;
	int worker_threads = 1;
	
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
	
	cout << "CLIENT STARTED:" << endl;

	cout << "Establishing control channel... " << flush;
	RequestChannel chan("control", RequestChannel::CLIENT_SIDE);
	cout << "done." << endl;;
	
	string hello_reply = chan.send_request("hello");
	cout << "Reply to request 'hello' is '" << hello_reply << "'" << endl;
	BoundedBuffer request_buffer(buffer_size);
	BoundedBuffer response_buffer(buffer_size);
	
	vector<string> names = {"Joe Smith", "Jane Smith", "John Doe"};
	
	int request_threads = names.size();
	int stat_threads = names.size();

	vector<pthread_t> threads(names.size()*2 + worker_threads);
	cout << "THREAD SIZE " << threads.size() << endl;
	
	for (int i = 0; i < names.size(); ++i) {
		RequestDetails* req_attr = new RequestDetails(names[i], &request_buffer, &request_threads, &request_count);
		
		pthread_t request_id = threads.at(i*2);
		pthread_create(&request_id, NULL, request_thread, (void*)req_attr);
		threads[i*2] = request_id;
		
		StatsDetails* stat_attr = new StatsDetails(names[i], &response_buffer);
		
		pthread_t stat_id = threads.at(i*2 + 1);
		pthread_create(&stat_id, NULL, stat_thread, (void*)stat_attr);
		threads[i*2+1] = request_id;
	}
	
	for (int i = 0; i < worker_threads; ++i) {
		WorkerDetails* attr = new WorkerDetails(&request_buffer, &response_buffer, &chan, &worker_threads);
		
		pthread_t worker_id = threads.at(names.size()*2 + i);
		pthread_create(&worker_id, NULL, worker_thread, (void*)&attr);
		threads[names.size()*2 + i] = worker_id;
	}

	for (pthread_t thread : threads) {
		pthread_join(thread, NULL);
	}
	
	string quit_reply = chan.send_request("quit");
	cout << "Reply to request 'quit' is '" << quit_reply << "'" << endl;
}

void * request_thread(void * _attr) {
	RequestDetails *attr = ((RequestDetails*)_attr);
	mutex_l.P();
	cout << "Request: START " << attr->name << " " << *attr->request_count << endl;
	mutex_l.V();
	for (int i = 0; i < *attr->request_count; ++i) {
		string request_string = "data " + attr->name;
		mutex_l.P();
		cout << "Request: (" << attr->name << ") " << request_string << endl;
		mutex_l.V();
		attr->buffer->push(request_string);
	}
	if (--(*attr->request_threads) == 0) {
		attr->buffer->push(QUIT_SIGIL);
	}
	delete attr;
	pthread_exit(0);
	return 0;
}

void * worker_thread(void * _attr) {
	WorkerDetails* attr = ((WorkerDetails*)_attr);

	mutex_l.P();
	string chan_name = attr->base_chan->send_request("newthread");
	cout << "Worker: (BASE) 'newthread' -> '" << chan_name << "'" << endl;
	mutex_l.V();
	RequestChannel chan(chan_name, RequestChannel::CLIENT_SIDE);
	for (;;) {
		string request_string = attr->in_buffer->pop();
		if (request_string == QUIT_SIGIL) {
			break;
		}
		string reply_string = chan.send_request(request_string);
		mutex_l.P();
		cout << "Worker: (" << chan_name << ") '" << request_string << "' -> '" << reply_string << "'" << endl;
		mutex_l.V();
		attr->out_buffer->push(reply_string);
	}
	attr->in_buffer->push(QUIT_SIGIL);
	if (--(*attr->worker_threads) == 0) {
		attr->out_buffer->push(QUIT_SIGIL);
	}
	string quit_response = chan.send_request("quit");
	mutex_l.P();
	cout << "Worker: (" << chan_name << ") 'quit' -> '" << quit_response << "'" << endl;
	mutex_l.V();
	delete attr;
	pthread_exit(0);
	return 0;
}

void * stat_thread(void * _attr) {
	StatsDetails* attr = ((StatsDetails*)_attr);

	for (;;) {
		string response_string = attr->buffer->pop();
		if (response_string == QUIT_SIGIL) {
			break;
		}
		mutex_l.P();
		//cout << "Stat: (" << attr->name << ") " << response_string << endl;
		mutex_l.V();
	}
	attr->buffer->push(QUIT_SIGIL);
	delete attr;
	pthread_exit(0);
	return 0;
}
