#ifndef NODEMNG_H
#define NODEKMNG_H

using namespace std;
#include <stdio.h>
#include <string>
#include <fstream>
#include "sysdefine.h"
#include "baseinfo.h"
#include "dtime.h"
// INSTALL_HOME/config/disk.conf
#define NODE_CONFIG "/config/node.conf"
#define NODENAMELIST  {(char *)"name",(char *)"system",(char *)"cluster",(char *)"config",NULL}
 
class nodeInfo :public baseInfo
{
public:
   nodeInfo();
   ~nodeInfo(){};
   //name:the directry.
   virtual int getStatus();
//   virtual int set(stringname,string );
   virtual int getInfoFromMap();
   int set(string name,string system,string cluster,int i );
   string system,cluster;
   //dtime m_tm;
//       char *buf;
    
 
};

class nodeMng :public baseMng
{
public:

   nodeMng();
   ~nodeMng();
   //typedef vector< diskInfo > DISKList;
 
   int loadNode();
   int saveNode();
   vector <nodeInfo> *  getList();
   //vector <nodeInfo> *  m_list;
  // virtual int add(nodeInfo *info);
  // nodeInfo * get(int i);
  // int size();

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

 
private:
    void init();
    




};

#endif
