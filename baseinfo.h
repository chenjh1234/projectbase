#ifndef BASEINFO_H
#define BASEINFO_H

using namespace std;
#include "sysdefine.h"
#include <stdio.h>
#include <string>
#include <vector>
#include <map>
#include "flexvar.h"

 
/**
 * abstract base class for data information.
 *  name,value pairs:
 *  name = value;  name:string ,value:flexVar
 *  numItems() : number of infomations:name-value,pairs
 *  names: name,config.....,config:
 */
class baseInfo
{
public:
   baseInfo(){};
   ~baseInfo(){ };
  
    /**
     * the current status it will renew continuously
     * 
     * @return int 
     */
  // virtual int set()=0;
   virtual int getStatus(){return 0;};
   //virtual int getInfoFromMap() =0;
   //virtual int getFromMap() = 0; // map value all in  string.implement by inheritor,If decode .
  
   virtual int set(string str,flexVar v)
   {
       m_map[str] = v;
       return 0;
   };

   stringList getNameList();

   int numItems()
   {
       return m_map.size();
   };

   enum CONFIG
   {
      OK,
      RO,
      OFF
   };
    
   string name;
   CONFIG config;
protected:
   map<string,flexVar > m_map;
   //stringList m_nameList;


};
/**
 * base manage for  basInfo
 * 
 * @author cjh (8/26/2014)
 */
class baseMng
{
public:
   baseMng();
   ~baseMng();
  
   int removeItem(char *name);
   int removeItem(int idx);
   int removeAll();
   int size();
   int find(char *name);
   baseInfo * get(int i);
   baseInfo * get(char *name);
    /**
     * print name,config 
     * 
     * @return int 
     */
   virtual int dump(); 

   int setConfigfile(char *);//get information from file some of the inheritor
   //virtual int getInfoFromMap(baseInfo &info ) =0;
  
 
protected:
   
   // the inheritors will compliments it l
   int load(char *filename);  ///  load m_list from config file,  for disk, node,etc
   int save(char *filename);  ///  save m_list to a config file,q
                              

   virtual int decode(string str){return 0;}; ///< string to baseInfo in each line in the file for load
   virtual string encode(int i){return " ";};   ///< baseInfo to string in each line in the file for save
   int add(baseInfo *info);  // if item not same 

   vector <baseInfo * >  *m_list;
   string m_configPathname;//for disk,node,
   string m_note; /// # note for the items in the baseInfo; first line of the config file,start '#'
    

};
 

#endif
