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
Mutex mutex_l;

int main(int argc, char * argv[]) {
	cout << "CLIENT STARTED:" << endl;

	cout << "Establishing control channel... " << flush;
	RequestChannel chan("control", RequestChannel::CLIENT_SIDE);
	cout << "done." << endl;;
	
	string hello_reply = chan.send_request("hello");
	cout << "Reply to request 'hello' is '" << hello_reply << "'" << endl;

	int buffer_size = 2000;
	BoundedBuffer request_buffer(buffer_size);
	BoundedBuffer response_buffer(buffer_size);
	vector<string> names = {"Joe Smith", "Jane Smith", "John Doe"};
	vector<pthread_t> threads;
	int request_threads = names.size();
	int worker_threads = 1;
	int stat_threads = names.size();
	int request_count = 10000;

	for (string name : names) {
		RequestDetails req_attr;
		req_attr.name = name;
		req_attr.buffer = &request_buffer;
		req_attr.request_threads = &request_threads;
		req_attr.worker_threads = &worker_threads;
		req_attr.request_count = request_count;
		pthread_t request_id;
		pthread_create(&request_id, NULL, request_thread, (void*)&req_attr);
		threads.push_back(request_id);

		StatsDetails stat_attr;
		stat_attr.buffer = &response_buffer;
		stat_attr.name = name;
		pthread_t stat_id;
		pthread_create(&stat_id, NULL, stat_thread, (void*)&stat_attr);
		threads.push_back(stat_id);
	}

	WorkerDetails attr;
	attr.in_buffer = &request_buffer;
	attr.out_buffer = &response_buffer;
	attr.base_chan = &chan;
	attr.worker_threads = &worker_threads;
	attr.stat_threads = &stat_threads;
	pthread_t worker_id;
	pthread_create(&worker_id, NULL, worker_thread, (void*)&attr);
	threads.push_back(worker_id);

	for (pthread_t thread : threads) {
		pthread_join(thread, NULL);
	}

	string quit_reply = chan.send_request("quit");
	cout << "Reply to request 'quit' is '" << quit_reply << "'" << endl;
}

void * request_thread(void * _attr) {
	RequestDetails attr = *((RequestDetails*)_attr);

	for (int i = 0; i < attr.request_count; ++i) {
		string request_string = "data " + attr.name;
		mutex_l.Lock();
		cout << "Request: (" << attr.name << ") " << request_string << endl;
		mutex_l.Unlock();
		attr.buffer->push(request_string);
	}
	if (--(*attr.request_threads) == 0) {
		for (int i = 0; i < *attr.worker_threads; ++i) {
			attr.buffer->push(QUIT_SIGIL);
		}
	}
	return 0;
}

void * worker_thread(void * _attr) {
	WorkerDetails attr = *((WorkerDetails*)_attr);

	string chan_name = attr.base_chan->send_request("newthread");
	mutex_l.Lock();
	cout << "Worker: (BASE) 'newthread' -> '" << chan_name << "'" << endl;
	mutex_l.Unlock();
	RequestChannel chan(chan_name, RequestChannel::CLIENT_SIDE);
	for (;;) {
		string request_string = attr.in_buffer->pop();
		if (request_string == QUIT_SIGIL) {
			break;
		}
		string reply_string = chan.send_request(request_string);
		mutex_l.Lock();
		cout << "Worker: (" << chan_name << ") '" << request_string << "' -> '" << reply_string << "'" << endl;
		mutex_l.Unlock();
		attr.out_buffer->push(reply_string);
	}
	if (--(*attr.worker_threads) == 0) {
		for (int i = 0; i < *attr.stat_threads; ++i) {
			attr.out_buffer->push(QUIT_SIGIL);
		}
	}
	string quit_response = chan.send_request("quit");
	mutex_l.Lock();
	cout << "Worker: (" << chan_name << ") 'quit' -> '" << quit_response << "'" << endl;
	mutex_l.Unlock();
	return 0;
}

void * stat_thread(void * _attr) {
	StatsDetails attr = *((StatsDetails*)_attr);

	for (;;) {
		string response_string = attr.buffer->pop();
		if (response_string == QUIT_SIGIL) {
			break;
		}
		mutex_l.Lock();
		cout << "Stat: (" << attr.name << ") " << response_string << endl;
		mutex_l.Unlock();
	}
	return 0;
}
