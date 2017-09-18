#ifndef BASETHREAD_H
#define BASETHREAD_H
using namespace std;
#include <pthread.h>
#include <iostream>
/**
 * base class for thread ,the successor have to implimemts :
 * connect() 
 * call run to start the thread. 
 * 
 * @author cjh (8/25/2014)
 * 
 * @param arg 
 * 
 * @return void* 
 */
void * _pthread_cb_(void *arg);

class baseThread
{
public:
   baseThread();
   virtual ~baseThread();
   virtual void connect() = 0;
   int run();
   void stop();
   pthread_t getId();
protected:
   pthread_t m_id;
   pthread_mutex_t mutex;
};



#endif
