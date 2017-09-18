#include "basesema.h"

baseSema::baseSema()
{
   init(0);
} 

baseSema::~baseSema()
{
   
} 
int baseSema::init(int p,int v)
{
   return sem_init(&m_sema,p,v);

}
int baseSema::init(int v)
{
   return sem_init(&m_sema,THREAD_SHARED,v);

}
int baseSema::init(char *s)
{
   return 0;

}
int baseSema::close()
{
   return sem_destroy(&m_sema);

}
int baseSema::acquire()
{
   return sem_wait(&m_sema);

}
int baseSema::release()
{
   return sem_post(&m_sema);
}
int baseSema::available()
{
   int i,v;
   i = sem_getvalue(&m_sema,&v);
   if (i ==0)
   {
      return v;
   }
   else
      return -1;
}
bool baseSema::tryAcquire()
{
  
   return sem_trywait(&m_sema);
    
}
bool baseSema::tryRelease()
{
   return sem_post(&m_sema);
}
   