#include "diskmng.h"
#include <istream>
#include "comfun.h"

diskInfo::diskInfo() 
{
   string str;
   int i;
  
  
   char *dirs[] = DISKNAMELIST;
   i = 0;
   while (dirs[i] !=NULL) 
   {
      str = dirs[i];
      //m_nameList.push_back(str);
      m_map[str] = flexVar(1);
      i++;
   } 
   set("1",0);
}
//==========================
int diskInfo::set(string n,int s )
{
    name = n;
    config = CONFIG(s);
    stringList strlist;
    strlist = getNameList();

    m_map[strlist[0]] = flexVar(name);
    m_map[strlist[1]] = flexVar(config);
    return 0;
} 
//==========================
 
int diskInfo::getInfoFromMap()
{
    string str,name;
    int i;
    //CONFIG config;
 
    map<string,flexVar>::iterator it;
   
    str = "";
    for (it = m_map.begin(); it != m_map.end();it++) 
    {
        if (it->first == "name") 
            name =  it->second.toString();
        if (it->first == "config") 
            i = atoi(it->second.toString().c_str());    
    }
    config = CONFIG(i);

    return 0;
} 
 
//==========================
#ifdef WIN32
int diskInfo::getStatus()
{
    return 0;
}
float diskInfo::getSpeed()
{
    return 100.;
}
#else
int diskInfo::getStatus()
{
    //fstream f;
    int i;
    string cmd,str;
    stringList strlist;
    char *line=NULL;
    size_t len;
    ssize_t ret;
    cmd = "df " + name;
    FILE *fp = popen(cmd.c_str(),"r");
 
    i = 0;
    if (fp !=NULL)
    {
        while (ret = getline(&line,&len,fp) != -1) 
        {
            
            i++;
            if (i == 1) continue;// skip 1st line
            //MPR3("line = %s,%d\n",line,len);
            str = line;
            strlist = splitStr(str);
            str = strlist[4]; // the fourth item is the percent of the space used
            str = str.substr(0,str.size() -1);
            //MPR2("per = %s, \n",str.c_str());
            space = atoi(str.c_str());
            //MPR2("space = %d \n",space);
        }
        pclose(fp);
        if (i == 0)  return -1;
        return space; 
    }
    else
    {
        MPR1("cannot get disk status\n");
        return -1;
    }
    return 0;
} 

//==========================
float diskInfo::getSpeed()
{
    //fstream f;
    int i;
    string cmd,str;
    size_t len;
    dtime tm;

    float f;
    double fd;
    int ret;
    char *buf;
    len = 10*1024*1024;//10M
//    buf = NULL;
    buf = new char[len];
   
    cmd = name + SLASH + "testspeed.data";
/*=========================================== 
use m_tm is core down :
diskspeed /s0/u/cjh/disk1= 626.527161 M/s
Abort (core dumped) 
 
if tm ,i use member of th class ,it will coredump sig abort when we use the second or more time of getspeed() 
   it oredump in (buf = new char[len]),
   use local tm is OK
*/
    //m_tm.start();
    tm.start();
    struct timeval tEnd;
    struct timeval tStart;
    gettimeofday( &tStart,NULL );
    FILE *fp = fopen(cmd.c_str(),"wb");
  
    i = 0;
    if (fp !=NULL)
    {

        //for (i =0; i<10; i++)
        ret = fwrite(buf, len, 1, fp); 
 
        if (ret >0)
        {
             
            //fd = m_tm.getElapsedTime();
            fd = tm.getElapsedTime();             
            f = (float) 10/fd;
 
        }
        else
        {
            MPR2("cannot write file for write ,diskname = %s\n",name.c_str());
            f=0;
        }
    }
    else
    {
        MPR2("cannot open file for write ,diskname = %s\n",name.c_str());
        f = 0;
    }

     
    fclose(fp);

    delete buf;
    return f;
} 
#endif
//========satrt mng=======================================================
void diskMng::init()
{

    //m_list = new vector<diskInfo> ;
    //baseMng::m_list = (vector<baseInfo *> *) m_list;
    m_list = (vector < baseInfo *> *) new vector<diskInfo *> ;
// have to do this two;
    setConfig();
    loadDisk();
}
//==========================
diskMng::diskMng()
{
    init();
}
//==========================
diskMng::~diskMng()
{
    delete m_list;
}
/*
diskInfo * diskMng::get(int i)
{

    if (i < size()) 
    {
        return &m_list->at(i); 
    }
    else
        return NULL;
    
}
int diskMng::size()
{
    return m_list->size();
}
*/
//==========================
int diskMng::setConfig()
{
    //note
    // tell th filename
    m_note = "# diskname config(OK=0,RO=1,OFF=2)";
    char * pPath;
    string name;

    pPath = getenv (INSTALL_HOME);

    if(pPath == NULL)
    {
        MPR1("INSTALL_HOME is not defined\n");
        return  -1;         
    }
 
    name = pPath ;
    name = name +  DISK_CONFIG;

    setConfigfile((char *)name.c_str());
    return 0;
}
int diskMng::saveDisk()
{
     
  
    if(save((char *)m_configPathname.c_str()) !=0)
        return -2;
 
    if (m_list->size() == 0) 
    {
      MPR1("Warning save disk end ,m_list empty\n");
      return -3;
    }
    else
      return 0;
}
int diskMng::loadDisk()
{
    //m_list->clear();
    removeAll();
    if(load((char *)m_configPathname.c_str()) !=0)
        return -2;
 
    if (m_list->size() == 0) 
    {
      MPR1("Warning load disk end ,m_list empty\n");
      return -3;
    }
    else
      return 0;
}

 
string diskMng::encode(int i)
{
    string str;
    str = m_list->at(i)->name + " "+ toStr(m_list->at(i)->config);
    return str;

}
int diskMng::decode(string strl)
{
    string str,name;
    stringList slist;
    diskInfo *di;
    char line[NAMELEN_MAX];
    char *r;
    di = new diskInfo();

    // cout << line<<endl;
    str = strl;
    slist = splitStr(str);
    if (slist.size() < 2 ) // name config.not valid
    {
        MPR2("Not Valid line = %s \n",str.c_str());
        return 1;
    }

    str = slist[0]; 
    if (!str.empty()) 
    {
        // name,config
        di->set(slist[0],atoi(slist[1].c_str()));
        add(di);
        return 0;
    }
    return 1;
    
}
/*
int diskMng::add(diskInfo *info)
{
  
    m_list->push_back( *info); 
//cout << "addddddddddddddddddd\n";
    return 0;
}*/
