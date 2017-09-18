#ifndef FILEMNG_H
#define FILEMNG_H

using namespace std;
#include <sys/stat.h>
#include <sys/types.h>
//#include <pwd.h>
#include <unistd.h>
#include <stdio.h>
#include <string>
#include <fstream>
#include "sysdefine.h"
#include "baseinfo.h"
#include "dtime.h"
#include "flexvar.h"
#include "comfun.h"
#include "projectmng.h"
#include "diskmng.h"
// INSTALL_HOME/config/disk.conf
 
#define FILEITEM_LIST  {(char*)"name",(char*)"size",(char*)"time",(char*)"path",(char *)"user",NULL}

class fileInfo :public baseInfo
{
public:
   fileInfo() ;
   ~fileInfo(){};
   //name:the directry.
    /**
     * get other info(name,time,size) according path

     * @return int 
     */
   virtual int getStatus();
    /**
     * set path ,and getStatus(); 
     * 
     * @param n 
     * 
     * @return int 
     */
   virtual int set(string path );
   virtual int getInfoFromMap();
   dtime m_tm;
   string path,time,user;
   int size;
   
};

class fileMng :public baseMng
{
public:

   fileMng();
   ~fileMng();
   char *getProjectHome();// move to comfun;
   virtual int setProject(char *p);
   virtual int setProject(char *p,char *l);
   //typedef vector< diskInfo > DISKList;

   string m_config;//type of the file:log,flow,job,data,table;
   int deleteFile(char *n);

   int loadFiles(string path);
   string getConfig();
protected:
    /**
     * set the file type: log ,for the dscent use
     * @param c 
     */
   void setConfig(string c);
private:
    void init(); 
    

};
//============log=============

class logMng :public fileMng
{
public:

   logMng():fileMng(){setConfig("log");};
   ~logMng(){delete m_list;};
};
//============flow=============
class flowMng :public fileMng
{
public:

   flowMng():fileMng(){setConfig("flow");};
   ~flowMng(){delete m_list;};
};
//============table=============
class tableMng :public fileMng
{
public:

   tableMng():fileMng(){setConfig("table");};
   ~tableMng(){delete m_list;};
};
//============job=============
class jobMng :public fileMng
{
public:

   jobMng():fileMng(){setConfig("job");};
   ~jobMng(){delete m_list;};
};

//============data=============
class dataMng :public fileMng
{
public:

   dataMng():fileMng(){setConfig("data");};
   ~dataMng(){delete m_list;};
   virtual int setProject(char *p);
   virtual int setProject(char *p,char *l);
};

#endif
/*    
void testfile()
{
    logMng log;
    fileInfo *fp;
    log.setProject((char *)"myproject1");

    cout << "size of files = " << log.size() <<endl;

    log.dump();
    int i ;
    for (i = 0 ; i <log.size() ; i++) 
    {
       fp =  (fileInfo *)(log.get(i));
       cout << fp->name <<endl;
       cout << fp->path <<endl;
       cout << fp->size <<endl;
       cout << fp->time <<endl;
       cout << fp->user <<endl;
    }

    cout << "======================\n";
    log.setProject((char *)"myproject",(char *)"line2");
    for (i = 0 ; i <log.size() ; i++) 
    {
       fp =  (fileInfo *)(log.get(i));
       cout << fp->name <<endl;
       cout << fp->path <<endl;
       cout << fp->size <<endl;
       cout << fp->time <<endl;
       cout << fp->user <<endl;
    }

}
*/
