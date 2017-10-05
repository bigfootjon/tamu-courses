/* 
    File: simpleclient.C

    Author: R. Bettati
            Department of Computer Science
            Texas A&M University
    Date  : 2012/07/11

    Simple client main program for MP2 in CSCE 313
*/

/*--------------------------------------------------------------------------*/
/* DEFINES */
/*--------------------------------------------------------------------------*/

    /* -- (none) -- */

/*--------------------------------------------------------------------------*/
/* INCLUDES */
/*--------------------------------------------------------------------------*/

#include <cassert>
#include <string>
#include <iostream>
#include <sstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>

#include <errno.h>
#include <unistd.h>

#include "reqchannel.h"
#include "dataserver.h"

using namespace std;

/*--------------------------------------------------------------------------*/
/* DATA STRUCTURES */ 
/*--------------------------------------------------------------------------*/

    /* -- (none) -- */

/*--------------------------------------------------------------------------*/
/* CONSTANTS */
/*--------------------------------------------------------------------------*/

    /* -- (none) -- */

/*--------------------------------------------------------------------------*/
/* FORWARDS */
/*--------------------------------------------------------------------------*/

    /* -- (none) -- */

/*--------------------------------------------------------------------------*/
/* LOCAL FUNCTIONS -- SUPPORT FUNCTIONS */
/*--------------------------------------------------------------------------*/

string int2string(int number) {
   stringstream ss;//create a stringstream
   ss << number;//add number to the stream
   return ss.str();//return a string with the contents of the stream
}

/*--------------------------------------------------------------------------*/
/* MAIN FUNCTION */
/*--------------------------------------------------------------------------*/

int main(int argc, char * argv[]) {
  if (!fork()) {
    main_dataserver();
    return 0;
  }
  
  cout << "CLIENT STARTED:" << endl;

  cout << "Establishing control channel... " << flush;
  RequestChannel chan("control", RequestChannel::CLIENT_SIDE);
  cout << "done." << endl;

  /* -- Start sending a sequence of requests */

  string reply1 = chan.send_request("hello");
  cout << "Reply to request 'hello' is '" << reply1 << "'" << endl;

  string reply2 = chan.send_request("data Joe Smith");
  cout << "Reply to request 'data Joe Smith' is '" << reply2 << "'" << endl;

  string reply3 = chan.send_request("data Jane Smith");
  cout << "Reply to request 'data Jane Smith' is '" << reply3 << "'" << endl;

  long total_musecs;

  for(int i = 0; i < 100; i++) {
    string request_string("data TestPerson" + int2string(i));
    struct timeval tp_start;
    struct timeval tp_end;
  
    gettimeofday(&tp_start, 0);
    string reply_string = chan.send_request(request_string);
    gettimeofday(&tp_end, 0);
    long sec = tp_end.tv_sec - tp_start.tv_sec;
    long musec = tp_end.tv_usec - tp_start.tv_usec;
    if (musec < 0) {
      musec += 1000000;
      sec--;
    }
    total_musecs += musec;
    printf("TIME [sec = %ld, musec = %ld, total_musec = %ld, total_count = %ld]\n", sec, musec, total_musecs, i);
	cout << "reply to request " << i << ":" << reply_string << endl;;
  }
 
  string reply4 = chan.send_request("quit");
  cout << "Reply to request 'quit' is '" << reply4 << "'" << endl;

  usleep(1000000);
}
