#ifndef _client_h_
#define _client_h_

#include "bounded_buffer.H"
#include "reqchannel.H"
#include <string>

void * request_thread(void * attr);
void * worker_thread(void * attr);
void * stat_thread(void * attr);

#endif
