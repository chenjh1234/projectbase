#include "baseinfo.h"
stringList baseInfo::getNameList()
{
    stringList strlist;
    map<string,flexVar> :: iterator it;

    for ( it=m_map.begin() ; it != m_map.end(); it++ )
    {
        strlist.push_back((*it).first );
    }
    return strlist;
}
baseMng::baseMng()
{
     
}

//===============================================
baseMng::~baseMng()
{
    //m_list.clear();
}
 
//===============================================
baseInfo * baseMng::get(int i)
{

    if (i < size()) 
    {
        return m_list->at(i); 
    }
    else
        return NULL;
    
}
baseInfo * baseMng::get(char *n)
{
    int i;
    //cout <<"find name = " <<n <<endl;
    i = find(n);
    //cout <<"i = "<<i <<endl;

    //if (i =find(n)>=0)
    if(i >=0 )
    {
         // cout <<"i = "<<i <<endl;
        return get(i);
    }
    return NULL;
}

//===============================================
int baseMng::removeItem(char *n)
{
    int i;
    string str;
    vector<baseInfo *>::iterator it;
 
    str = n;
    for (it = m_list->begin(); it != m_list->end(); it ++ ) 
    {
         
        if ((*it)->name == n) 
        {
            delete (*it);
            m_list->erase(it);
            return 0;
        } 
    }
     
    return -1 ;
}
//===============================
int baseMng::removeAll()
{
    int i,ret;
    string str;
    for (i = m_list->size()-1;i >= 0; i--)
    {
        ret = removeItem(i);
        if (ret !=0) 
        {
            return i;
        }
    }
    return 0;
}
//===============================================
int baseMng::removeItem(int idx)
{
    int i;
    string str;
    if (idx >= m_list->size() || idx <0) 
    {
        return -1;
    }
    str = m_list->at(idx)->name;
    return removeItem((char *)str.c_str());
}
int baseMng::size()
{
    return m_list->size();
}

//===============================================
int baseMng::find(char *n)
{
    int i;
    string str;
    vector<baseInfo *>::iterator it;
//    cout << "1111111\n";
//     MPR2("find = %s\n",n);
    str = n;
    i =0;
    for (it = m_list->begin(); it != m_list->end(); it ++ ) 
    {
         
        if ((*it)->name == n) 
        {
            //MPR2("find return= %d\n",i);
            return i;
        } 
        i++;
    }
     
    return -1 ;
    
}

//===============================================
int baseMng::dump()
{
    int i;
    for (i = 0;i < size(); i++) 
    {
        MPR4("%d:  %s   %d\n",i,m_list->at(i)->name.c_str(),m_list->at(i)->config);
    }
    return 0;
}
 
//===============================================
int baseMng::setConfigfile(char *ch)
{
    m_configPathname = ch;
    return 0;
}

//===============================================
int baseMng::load(char *filename)
{
    string str,name;
    char line[NAMELEN_MAX];

    name = filename;

    fstream f;
    f.open(name.c_str() ,fstream::in | fstream::out | fstream::app);
    if (f.fail())
    {
        MPR2("CONFIG path is not exist,name = %s\n",name.c_str());
        return -1;
    }


    if (!f.fail())
    while (!f.eof()) 
    {
        f.getline(line,NAMELEN_MAX);  
//        p = 0;
        str = line;
        if (str.empty()) continue;
        if (str.at(0) == '#') continue; 

        if(decode(str) != 0)
        {
            MPR2("Decode error ,line  = %s\n",str.c_str());
            return -2;
        }
        
    }//endof line
    return 0;
}
//===============================================
int baseMng::save(char *filename)
{
    int i;
    string str,name;
    name = filename;

    fstream f;
    f.open(name.c_str() , fstream::out | fstream::trunc);
    if (f.fail())
    {
        MPR2("CONFIG file open error,name = %s\n",name.c_str());
        return -1;
    }

    str = m_note;
    if (! m_note.empty()) 
        f << str << endl; 
 //   encode;
 
    for (i = 0 ;i <m_list->size(); i++) 
    {
        //str = m_list->at(i).name + " "+ toStr(m_list->at(i).config);
        str = encode(i);
        f << str <<endl;   
    }
 
    f.close();

    return 0;
}

//===============================================
  
int baseMng::add(baseInfo *info)
{
  
    m_list->push_back( info); 

    return 0;
} 
 
/*
string baseMng::encode(int idx)
{
    string str;
    baseInfo info;
    int i;
    int size ;

    info = m_list->at(idx);
    size = info.m_map.size();

    map<string,flexVar>::iterator it;
    str = "";
    for (it = info.m_map.begin(); it != info.m_map.end();it++) 
    {
        str = str + it->second.toString() + " ";
    }
   // str = m_list->at(i).name + " " + toStr(m_list->at(i).config); 
    return str;

}
int baseMng::decode(string strl)
{
    string str,name;
    stringList slist;
    baseInfo info;
    char line[NAMELEN_MAX];
    char *r;

    // cout << line<<endl;
    str = strl;
    slist = splitStr(str);
    str = slist[0]; 
    if (str.empty()) 
        return -1;

//    size = info.m_map.size();

    map<string,flexVar>::iterator it;

    int i;
    i = 0;
    for (it = info.m_map.begin(); it != info.m_map.end(); it++) 
    {
        it->second = flexVar(slist[i]);
        i++;
    }
    getInfoFromMap(info);
    add(info);

    return 0;
    
}
  */

