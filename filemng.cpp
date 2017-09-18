#include "filemng.h"
#include <istream>
#include "comfun.h"
#include <QDateTime>

fileInfo::fileInfo() 
{
   string str;
   int i;
  
  // file item
   char *dirs[] = FILEITEM_LIST;
   i = 0;
   while (dirs[i] !=NULL) 
   {
      str = dirs[i];
      m_map[str] = flexVar(1);
      i++;
   } 
}
//==========================
int fileInfo::set(string path1 )
{
   path = path1;
   return getStatus();
} 
//==========================
 
int fileInfo::getInfoFromMap()
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
        if (it->first == "size") 
            size = atoi(it->second.toString().c_str()); 
        if (it->first == "time") 
            time =  it->second.toString().c_str();    
        if (it->first == "path") 
            path =  it->second.toString().c_str(); 
        if (it->first == "user") 
            user =  it->second.toString().c_str();    
    }
    config = CONFIG(0);
     
    return 0;
} 
 
//==========================
int fileInfo::getStatus()
{
    int i,uid;
    QString str;
    str =  path.c_str();
    QFileInfo info(str);
    name = info.fileName().toUtf8().data();
    size = info.size();
    time = info.created().toString().toUtf8().data();
    user = info.owner().toUtf8().data();
    config = CONFIG(0);

    stringList strlist;
    strlist = getNameList();

    m_map[strlist[0]] = flexVar(name);
    m_map[strlist[1]] = flexVar(size);
    m_map[strlist[2]] = flexVar(time);
    m_map[strlist[3]] = flexVar(path);
    m_map[strlist[4]] = flexVar(user);

    return 0;
    
} 
 
//========satrt mng=======================================================
void fileMng::init()
{

    //m_list = new vector<fileInfo> ;
    //baseMng::m_list = (vector<baseInfo *> *) m_list;
    m_list = (vector < baseInfo *> *) new vector<fileInfo *> ;
// have to do this two;
    //setConfig();
    //loadDisk();
}
//==========================
fileMng::fileMng()
{
    init();
}
//==========================
fileMng::~fileMng()
{
    //delete m_list;
}
//==========================
int fileMng::deleteFile(char *n)
{
    int i;
    string str;
    i = find(n);
    if (i <0)  return -1;
    fileInfo *fi;
    fi = (fileInfo *)m_list->at(i);
    str = fi->path;
    if(remove(str.c_str()) == 0)// remove file
        return removeItem(n);// remove from m_list
    else
        return -1;
}
//==========================
int fileMng::loadFiles(string path)
{
    stringList filelist;
    string str;
    fileInfo *fi;
    int i;


    filelist = dirFiles((char *)path.c_str());
    //MPR1("yyyyyyyyy\n");
    for (i = 0; i <filelist.size(); i ++) 
    {
        str = filelist[i];

        fi = new fileInfo;
        fi->set(str);
        m_list->push_back(fi);

    }
    return 0;
}
void fileMng::setConfig(string  p)
{
   m_config = p;

};
string fileMng::getConfig()
{
    return m_config;
}
char * fileMng::getProjectHome()
{
    return getProjectDir();
}
int fileMng::setProject(char * p)
{
   string str;
   str = string(getProjectHome());
   str = str + SLASH + string(p) + SLASH + m_config;
   //MPR2("dir = %s\n",str.c_str());
   removeAll();
   loadFiles(str);
   return 0;

};
//
int fileMng::setProject(char* p,char *l)
{
   string str;
   str = string(getProjectHome());
   str = str + SLASH + string(p) +SLASH + string(l) + SLASH + m_config;
   removeAll();
   loadFiles(str);
   return 0;
};
//===============================dataMng===================


int dataMng::setProject(char* p,char *l)
{
   diskMng dsk;
   diskInfo *di;
   string str;
   int i ;

   i = removeAll();
     // MPR2("remove =++++++++++++ %d\n",i);
   // add project directory;
   str = getProjectHome() ;
   str = str + SLASH + string(p)+SLASH + string(l)+ SLASH +"data";
   loadFiles(str);
   for (i = 0; i < dsk.size(); i++) 
   {
       di = (diskInfo *)dsk.get(i);
       str = di->name;
       str = str + SLASH + string(p)+SLASH + string(l);
       loadFiles(str);
   }
   return 0;

};
int dataMng::setProject(char * p)
{
   diskMng dsk;
   diskInfo *di;
   string str;
   int i ;
   i = removeAll();
   //MPR1("setProject\n");
   //MPR2("remove = ++++++++++++ %d\n",i);
      str = getProjectHome() ;
   str = str + SLASH + string(p) + SLASH +"data";
   loadFiles(str);

   for (i = 0; i < dsk.size(); i++) 
   {
       di = (diskInfo *)dsk.get(i);
       str = di->name;
       str = str + SLASH + string(p);
       loadFiles(str);
   }
   return 0;
};
