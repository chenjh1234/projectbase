#ifndef BASESEMA_H
#define BASESEMA_H
using namespace std;
#include <semaphore.h>
#include <iostream>
#define THREAD_SHARED 0
#define PROCESS_SHARED 1
 
/**
 * base class for sem : 
 * default:init(0,0); 
 * 
 * @author 
 */
class baseSema
{
public:
   baseSema();
   virtual ~baseSema();
   int init(int pshared,int v);
   int init(int v);
   int init(char *file);// not yet.
   int acquire();
   int release();
   int available();
   bool tryAcquire();
   bool tryRelease();
   int close();
    
protected:
   sem_t m_sema;
};



#endif
