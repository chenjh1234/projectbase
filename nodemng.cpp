#include "nodemng.h"
#include <istream>
#include "comfun.h"

nodeInfo::nodeInfo() 
{
   string str;
   int i;
   char *dirs[] = NODENAMELIST;
   i = 0;
   while (dirs[i] !=NULL) 
   {
      str = dirs[i];
      m_map[str] = flexVar(1);
      //m_nameList.push_back(str);
      i++;
   } 
   set("node1","rh2.6","cluster0",CONFIG(OK));
}
//==========================
int nodeInfo::set(string name1,string system1,string cluster1,int ic )
{
    int i;
    i = 0;
    //set(m_nameList[i],flexVar(name1));
    stringList strlist;
    strlist = getNameList();

    m_map[strlist[i]] = flexVar(name1);i++; 
    m_map[strlist[i]] = flexVar(system1);i++;
    m_map[strlist[i]] = flexVar(cluster1);i++;
    m_map[strlist[i]] = flexVar(ic);
    name = name1;
    system = system1;
    cluster = cluster1;
    config = CONFIG(ic);

    return 0;
} 
//==========================
 
int nodeInfo::getInfoFromMap()
{
    //cout <<"111111\n";
    string str,name;
    int i;
    //CONFIG config;
 
    map<string,flexVar>::iterator it;
    //cout <<"111111\n";
    str = "";
    if (m_map.empty())
    {
        return -1;
    }
    for (it = m_map.begin(); it != m_map.end(); it++) 
    {
        if (it->first == "name") 
            name =  it->second.toString();
        if (it->first == "system") 
            system =  it->second.toString();
        if (it->first == "cluster") 
            cluster =  it->second.toString();
        if (it->first == "config") 
            i = atoi(it->second.toString().c_str());    
    }
    config = CONFIG(i);
    return 0;
} 
  
//===========================================
#ifdef WIN32
int nodeInfo::getStatus()
{
    return 0;
}
#else
int nodeInfo::getStatus()
{
    //fstream f;
    int i,space;
    string cmd,str;
    stringList strlist;
    char *line=NULL;
    size_t len;
    ssize_t ret;
    cmd = "rsh " + name + " pwd";
    FILE *fp = popen(cmd.c_str(),"r");
 
    str = "";
    if (fp !=NULL)
    {
        while (ret = getline(&line,&len,fp) != -1) 
        {
            str = line;
            MPR2(" pwd = %s\n",str.c_str());
        }
        pclose(fp);
    }
    else
    {
        perror("popen");
        MPR1("cannot get node status\n");
        return -1;
    }
    if (str.empty()) 
    {
        return -1;
    }
    return 0; 
} 
#endif
//===============start mng================================================
void nodeMng::init()
{
    //m_list = new vector<nodeInfo> ;
    m_list = (vector < baseInfo *> *) new vector<nodeInfo *> ;
    //baseMng::m_list = (vector < baseInfo > *)m_list ;
    
// have to do this two;
    setConfig();
    loadNode();
}
//===============================================================
nodeMng::nodeMng()
{
    init();
}
//===============================================================
nodeMng::~nodeMng()
{
    delete m_list;
}
/*
int nodeMng::size()
{
    return m_list->size();
}

//===============================================================
nodeInfo * nodeMng::get(int i)
{

    if (i < size()) 
    {
        return &m_list->at(i); 
    }
    else
        return NULL;
    
} 
*/ 
//=============================
int nodeMng::setConfig()
{
    //note
    // tell th filename
    m_note = "# nodename(sn1) system(RH6.4) cluster(cluster1) config(OK=0,RO=1,OFF=2)";
    char * pPath;
    string name;

    pPath = getInstallDir();

    if(pPath == NULL)
    {
        MPR1("INSTALL_HOME is not defined\n");
        return  -1;         
    }
 
    name = pPath ;
    name = name +  NODE_CONFIG;

    setConfigfile((char *)name.c_str());
    return 0;
}
//===============================================================
int nodeMng::saveNode()
{
     
  
    if(save((char *)m_configPathname.c_str()) !=0)
        return -2;
 
    if (m_list->size() == 0) 
    {
      MPR1("Warning load node end ,m_list empty\n");
      return -3;
    }
    else
      return 0;
}
//===============================================================
int nodeMng::loadNode()
{
    //m_list->clear();
    removeAll();
    if(load((char *)m_configPathname.c_str()) !=0)
        return -2;
 
    if (m_list->size() == 0) 
    {
      MPR1("Warning load node end ,m_list empty\n");
      return -3;
    }
    else
      return 0;
}
//===============================================================
string nodeMng::encode(int i)
{
    string str;
    vector<nodeInfo> *mlist;
    mlist =( vector<nodeInfo> *)m_list;
    
    str = mlist->at(i).name + " ";
    str = str + mlist->at(i).system + " ";
    str = str + mlist->at(i).cluster + " ";
    str = str + toStr(mlist->at(i).config);
    return str;

}
//===============================================================
int nodeMng::decode(string strl)
{
    string str,name;
    stringList slist;
    nodeInfo *di;
    char line[NAMELEN_MAX];
    char *r;
    di = new nodeInfo();

    // cout << line<<endl;
    str = strl;
    slist = splitStr(str);
    if (slist.size() < 4 ) // name config.not valid
    {
        MPR2("Not Valid line = %s \n",str.c_str());
        return 1;
    }

    str = slist[0];
    /* 
    MPR2("strl=%s\n",strl.c_str());
    MPR2("str0=%s\n",slist[0].c_str());
    MPR2("str1=%s\n",slist[1].c_str());
    MPR2("str2=%s\n",slist[2].c_str());
    MPR2("str3=%s\n",slist[3].c_str());*/
    if (!str.empty()) 
    {
        // name,config
        di->set(slist[0],slist[1],slist[2],atoi(slist[3].c_str()));
        add(di);
        //cout << "size of m_list = " << m_list->size() << endl;
        return 0;
    }
    return 1;
    
}
vector <nodeInfo> * nodeMng::getList()
{
    return (vector <nodeInfo> *) m_list;
}
/*
int nodeMng::add(nodeInfo *info)
{
  
    m_list->push_back( *info); 
//cout << "addddddddddddddddddd\n";
    return 0;
}
  */

