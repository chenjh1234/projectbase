#ifndef DISKMNG_H
#define DISKMNG_H

using namespace std;
#include <stdio.h>
#include <string>
#include <fstream>
#include "sysdefine.h"
#include "baseinfo.h"
#include "dtime.h"
#include "flexvar.h"
// INSTALL_HOME/config/disk.conf
#define DISK_CONFIG "/config/disk.conf"
#define DISKNAMELIST  {(char*)"name",(char*)"config",NULL}

class diskInfo :public baseInfo
{
public:
   diskInfo() ;
   ~diskInfo(){};
   //name:the directry.
   virtual int getStatus();
   virtual int set(string n,int s );
   virtual int getInfoFromMap();

   float getSpeed();
   int space;
   dtime m_tm;
//       char *buf;
    
 
};

class diskMng :public baseMng
{
public:

   diskMng();
   ~diskMng();
   //typedef vector< diskInfo > DISKList;
 
   int loadDisk();
   int saveDisk();
 //  vector <diskInfo> *m_list;
//   int add(diskInfo *info);
//   int size();
//   int getInfoFromMap(diskInfo &info); 
  
   //diskInfo * get(int i);

   //int numDisks();df
  // DISKList diskList;
   //virtual int add(baseInfo *info);
   //virtual int remove(char *n);
  // virtual int size();
  // virtual bool find(char *);
   //virtual int dump();
    /**
     *  set the config file, 
     *  set note to comment the config file:
     *  #m_note = "# diskname config(OK=0,RO=1,OFF=2)";
     *  
     * @return int 
     */
   int setConfig();
    /**
     * 
     * decode string to diskInfo information
     *  
     * @param str 
     *  string to decode 
     * 
     * @return int 
     */
    virtual int decode(string str);
    /**
     * encode diskInfo information to a string 
     * like: name config

     * @param i 
     *  index of the  diskInfoList:m_list; 
     * 
     * @return string 
     *    encode result 
     */
    virtual string encode(int i);
    //virtual int  add(diskInfo *info);

//   vector <diskInfo > m_list;
private:
    void init();
    




};

#endif
