#include "basethread.h"
void * _pthread_cb_(void *arg)
{
   baseThread *c = (baseThread *)( arg);
   if(c)
   {
      //cout << "in thread\n";
      c->connect();
   }
   else
      c->stop();
   return NULL;
}
baseThread::baseThread()
{
   pthread_mutex_init(&mutex,NULL);

}
baseThread::~baseThread()
{

}
int baseThread::run()
{
   int i;
   i = pthread_create(&this->m_id,NULL,_pthread_cb_,this);
   //cout << "id=====" <<m_id << endl;
   //return pthread_join(this->id,NULL);
   return i;

}
void baseThread::stop()
{
   pthread_exit(NULL);

}
pthread_t  baseThread::getId()
{
   return this->m_id;

}
