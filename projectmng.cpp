
#include "projectmng.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

 
projectMng::projectMng()
{
   init();
}
projectMng::projectMng(char * name)
{
   
   init();
   setProject(name);
}
projectMng::~projectMng()
{

}
int projectMng::setLine(char *name)
{
   
   m_bExist = isLineExist(name);
   if (m_bExist) 
   {
      m_line = name;
      //getLineList();
      return 0;
   }
   else 
      return -1;

}
int projectMng::setProject(char *name)
{
   
   m_bExist = isProjectExist(name);
   if (m_bExist) 
   {
      m_name = name;
      m_line ="";
      getLineList();
      return 0;
   }
   else 
      return -1;

}
int projectMng::init()
{
   int i;
   char *dirs[] =   DIRS;
   char *ch;
   string str,logfile;
   //cout << "init ";
   m_name = "";
   m_line = "";
   str = ".";
 
   getProjectList();
   //qDebug() << "str0 = " << str.c_str() <<ch;
   ch = getProjectHome();
   //qDebug() << "str1 = " << str.c_str() <<ch;
   if (ch !=NULL) 
   {
       str = ch;
   }
    
 // logfile ="$PROJECT_HOME/.project.log
  
   logfile = str +  PROJECT_LOG;
   log = new logFile(logfile.c_str());
    
   //log = new logFile();
   // dirs
   
   i = 0;
   while (dirs[i] !=NULL) 
   {
      str = dirs[i];
      dirList.push_back(str);
      i++;
   }
   return 0;
 
}
int projectMng::createProjectDirs(char * name)
{
   string str,user,date;
   int i,ret;
  
   str = getProjectHome() + string(SLASH) + name;
//create projectInfo dir:
   i = mkDir(str.c_str());
   if(i == 0)
   {   
      log->warning("create project ,cannot create directory!! %s %s","name = ",name);
      return -2;// canot create dir;
   }
// create subdirs in the project:
   i = createDirs((char *)str.c_str());
   if(i != 0)
   {   
      log->warning("create project ,cannot create directorys in th project!! %s %s","name = ",name);
      return -3;// canot create dirs ;
   }
// crete seismic data dirs  :
   diskMng disk;
   if (disk.size() <=0) 
   {
       log->warning("create project ,No diskconfig file!! %s %s","name = ",name);
       MPR3("create project ,No diskconfig file!! %s %s","name = ",name);
       return 0;
   }
   for (i = 0; i < disk.size(); i++) 
   {
       str = disk.get(i)->name + string(SLASH) + name + "/data";//2015.7
       ret = mkDir(str.c_str());
       if (ret == 0) 
       {
           log->warning("create project ,cannot create Seismic DIR!! %s %s","name = ",name);
           MPR3("create project ,cannot create Seismic DIR!! %s %s","name = ",name);
           return -5;
       }
   }
   return 0;
}
int projectMng::createLineDirs(char * name)
{
   string str,user,date;
   int i,ret;

   str = getProjectHome() + string(SLASH) + m_name + string(SLASH) + name;
 
//create line infor dir:
   i = mkDir(str.c_str());
   if(i == 0)
   {   
      log->warning("create line ,cannot create directory!! %s %s/%s","name = ",m_name.c_str(),name);
      MPR4("create line ,cannot create directory!! %s %s/%s","name = ",m_name.c_str(),name);
      return -2;// canot create dir;
   }
   // crete dirs in the line:
   i = createDirs((char *) str.c_str());
   if(i != 0)
   {   
      log->warning("createLine ,cannot create directorys in the Line!! %s %s","name = ",name);
      MPR3("createLine ,cannot create directorys in the Line!! %s %s","name = ",name);
      return -3;// canot create dirs ;
   }

// crete seismic data dirs in line :
   diskMng disk;
   if (disk.size() <=0) 
   {
       log->warning("create line  ,No diskconfig file!! %s %s","name = ",name);
       MPR3("create line ,No diskconfig file!! %s %s","name = ",name);
       return 0;
   }
   for (i = 0; i < disk.size(); i++) 
   {
       str = disk.get(i)->name + string(SLASH) + m_name + string(SLASH) + name +"/data";
       ret = mkDir(str.c_str());
       if (ret == 0) 
       {
           log->warning("create liine ,cannot create Seismic DIR!! %s %s","name = ",str.c_str());
           MPR3("create line ,cannot create Seismic DIR!! %s %s","name = ",str.c_str());
           return -5;
       }
   }
   return 0;
}
   
int projectMng::createProject(char * name)
{
   string str,user,date;
   int i,ret;
   str = name;
// is exist:
   if(isProjectExist(name))
   {
      log->warning("create project ,project already exist!! %s %s ","name = ",name);
      return -1;
   }
// crete dirs:

   //cjh more code will added 
   i = createProjectDirs(name);
   if (i !=0) 
   {
       removeProjectDirs(name);
       return i;
   }
// add to projectList:
   str = name;
   user = getUser();
   date = m_tm.cdate();

   projectInfo pi;
   pi.set(str,user,date);
   // add info:
   projectList.push_back(pi);

//success: save to file;

   saveProjects();
   log->tline("create project ,OK!! %s %s ","name = ",name);
// turn the default to new project
   m_name = str;
   m_bExist = isProjectExist(name);
   return 0;

}
char * projectMng::getProjectHome()
{
    //qDebug()<< "getprojecthomein";
    return getProjectDir();
}
int projectMng::removeProjectDirs(char * name)
{
   string str,user,date;
   int i,j,ret;
   ret = 0;
   str = getProjectHome() + string(SLASH) + name;
//remove dir:
   //str = "rm -rf " +str;
   i = rmDir(str.c_str());
   if(i != 0)
   {   
      log->warning("remove project ,cannot remove Infor directory!! %s %s","name = ",name);
      ret= -2;// canot create dir;
   }
// seismic data dir:
   diskMng disk;
   if (disk.size() <=0) 
   {
       log->warning("remove project ,No diskconfig file!! %s %s","name = ",name);
       MPR3("remove project ,No diskconfig file!! %s %s","name = ",name);
       ret = 0;
       return ret;
   }
   for (i = 0; i < disk.size(); i++) 
   {
       str = disk.get(i)->name + string(SLASH) + name;
       //str = "rm -rf " +str;
       //MPR1(str.c_str());
       j = rmDir(str.c_str());
       if(j !=0)
       {   
           log->warning("remove project ,cannot remove Seismic directory!! %s %s","name = ",str.c_str());
           MPR3("remove project ,cannot remove Seismic directory!! %s %s","name = ",str.c_str());
           ret = -4;// canot create dir;
       }

   }
   return ret;
}
int projectMng::removeProject(char * name)
{
   string str,user,date;
   int i;
   str = name;
// dirs:
   if(!isProjectExist(name))
   {
      log->warning("remove project ,project is not exist!! %s %s ","name = ",name);
      return -1;
   }
//dirs:
   i = removeProjectDirs(name) ;
   if (i <-3) 
   {
       return i;
   }
 
// remove to projectList:
   str = name;

// if project exist:
   for (i = 0 ; i <projectList.size(); i++) 
   {
      if(str == projectList[i].name) 
      {
         projectList.erase(projectList.begin() +i);
          
      }
   } 
 
//success: save to file;

   saveProjects();
// remove project infor file:
   string fname;
   str =name; 
   fname = getProjectHome();
   fname = fname + PROJECT_LINE_INFO +str;
   remove(fname.c_str());

   log->tline("remove project ,OK!! %s %s ","name = ",name);
// turn the default to new project
   m_name = "";
   m_bExist = false;
   return 0;
}
int projectMng::removeLineDirs(char * name)
{
   string str,user,date;
   int i,ret,j;
   str = getProjectHome() + string(SLASH) + m_name + string(SLASH) + name ;
   ret = 0;

//remove dir:
   //i = mkdir(str.c_str(),S_IRWXU|S_IRWXG);
   //str = "rm -rf " +str;
   //i = system(str.c_str());
   i = rmDir(str.c_str());
   if(i != 0)
   {   
      log->warning("removeline ,cannot remove directory!!%s %s/%s ","name = ",m_name.c_str(),name);
      MPR4("removeline ,cannot remove directory!!%s %s/%s ","name = ",m_name.c_str(),name);
      //return -2; 
      ret = -2;// do all the remove :
   }
   // seismic data dir:
   diskMng disk;
   if (disk.size() <=0) 
   {
       log->warning("remove project ,No diskconfig file!! %s %s","name = ",name);
       MPR3("remove project ,No diskconfig file!! %s %s","name = ",name);
       //return -3;
       ret = 0;
       return ret;
   }
   for (i = 0; i < disk.size(); i++) 
   {
       str = disk.get(i)->name + string(SLASH) + m_name +string(SLASH) + name;;
       //str = "rm -rf " +str;
       j = rmDir(str.c_str());
       if(j != 0)
       {   
           log->warning("remove project ,cannot remove Seismic directory!! %s %s","name = ",str.c_str());
           MPR3("remove project ,cannot remove Seismic directory!! %s %s","name = ",str.c_str());
           //return -4;// canot create dir;
           ret = -4;
       }

   }
   return ret;
}

int projectMng::removeLine(char * name)
{
   string str,user,date;
   int i;
   str = name;
   if(!isLineExist(name))
   {
      log->warning("remove Line ,Line is not exist!! %s %s/%s ","name = ",m_name.c_str(),name);
      return -1;
   }
   i = removeLineDirs(name);
   if (i !=0) return i; 
// remove to lineList:

   str = name;

// if project exist:
   for (i = 0 ; i <lineList.size(); i++) 
   {
      if(str ==lineList[i].name) 
      {
         lineList.erase(lineList.begin() +i);
          
      }
   }
 
//success: save to file;

   saveLines();
   log->tline("remove Line ,OK!! %s %s/%s ","name = ",m_name.c_str(),name);
// turn the default to new project
   //m_name = "";
   //m_bExist = false;
   return 0;
}
int projectMng::createLine(char * name)
{
   string str,user,date;
   int i,ret;
   str = name;
//exist?
   if(isLineExist(name))
   {
      log->warning("create Line ,Line already exist!! %s %s/%s ","name = ",m_name.c_str(),name);
      return -1;
   }
//project selected?
   if (m_name.empty()) 
   {
       log->warning("create Line ,No project selected!! %s %s  ","name = ", name);
      return -1;
   }
 
//create dir:
   i = createLineDirs(name);
   if(i !=0)
   { 
      removeLineDirs(name);   
      return -1;
   }
// add to lineList:

   str = name;
   user = getUser();
   date = m_tm.cdate();

   projectInfo pi;
   pi.set(str,user,date);
   // add info:
   lineList.push_back(pi);

//success: save to file;

   saveLines();
   log->tline("create line ,OK!! %s %s/%s ","name = ",m_name.c_str(),name);
// turn the default to new project
   //m_name = str;
   //m_bExist = isLineExist(name);
   return 0;

}
int projectMng::createDirs(char *baseDir)
{
   int i,r;
   string base,str;
   char *dirs[] = DIRS;
   base = baseDir;

   for (i = 0; i <dirList.size() ;i ++) 
   {
      str = string(baseDir) + string(SLASH) + dirList[i];
      //create dir:
      r = mkDir(str.c_str());
      if (r ==0) 
      {
          return -1;
      }
   }
   return 0;

}
 
  
bool projectMng::isProjectExist(char * name)
{
   int i;
   string str;
   str = name;

// if project exist:
   for (i = 0 ; i <projectList.size(); i++) 
   {
      if(str == projectList[i].name) 
      {
         return true;//project exist;
      }
   }
   return false;

}
bool projectMng::isLineExist(char * name)
{
   int i;
   string str;
   str = name;
   if (m_name.empty()) 
   {
      return false;
   }

// if project exist:
   for (i = 0 ; i <lineList.size(); i++) 
   {
      if(str == lineList[i].name) 
      {
         return true;//project exist;
      }
   }
   return false;

}

int projectMng::numProjects()
{
   return projectList.size();
}
int projectMng::numLines()
{
   return lineList.size();
}
LINEList projectMng::getLineList()
{
   loadLines();
   return lineList;
}
int projectMng::getDiskList()
{
   return 0;
}
PROJECTList projectMng::getProjectList()
{
   
   loadProjects();
 //  saveProject();
   return projectList;

}
int projectMng::saveProjects()
{
   fstream f;
   int i,ret,p;
   string str,name;
   if (getProjectHome() ==NULL) 
   {
       MPR1("PROJECT_HOME not defined\n");
       return -1;
   }
   name = getProjectHome(); 
   name = name + PROJECT_INFO;
   
   f.open(name.c_str() ,fstream::out | fstream::trunc);

   str = "# projectname username date";
   f <<str<<endl;

   for (i = 0 ;i <projectList.size(); i++) 
   {
      str = projectList[i].name + " "+projectList[i].user +" "+projectList[i].date;
      //cout << str.c_str() <<endl;
      if (str.empty()) continue;
      f << str << endl;
   }
   f.close();
   return 0;
}
int projectMng::saveLines()
{
   fstream f;
   int i,ret,p;
   string str,name,project;
  if (m_name.empty()) 
   {
      // log->warning(" No project selected!! %s %s  ","name = ", " ");
      return -1;
   }
   project = m_name;
   name = getProjectHome();
   name = name + PROJECT_LINE_INFO +project;

   
   f.open(name.c_str() ,fstream::out | fstream::trunc);

   str = "# projectname username date";
   f <<str<<endl;

   for (i = 0 ;i <lineList.size(); i++) 
   {
      str = lineList[i].name + " "+lineList[i].user +" "+lineList[i].date;
      //cout << str.c_str() <<endl;
      f << str <<endl;   
   }
   f.close();
   return 0;
}
string projectMng::getCurrentProject()
{
  // cout << "name = " <<m_name <<endl;
   //string s;
  // s="12345"; 
  
   return m_name;

}
string projectMng::getCurrentLine()
{
   
   return m_line;

}
string projectMng::getLineHome(char * p)
{
   char * pPath;
   string pstr,lstr;

   pPath = getProjectHome();
   pstr = getCurrentProject();
   if (pstr.empty())  
       return pstr;

   lstr = string(pPath) + SLASH + pstr + SLASH + string(p); 
   return lstr;

}
string projectMng::getProjectHome(char * p)
{
   char * pPath;
   string str;
   pPath = getProjectHome();
   str = pPath;
   str = str + SLASH + string(p);
   return str;

}
 
int projectMng::loadProjects()
{
   fstream f;
   projectInfo pi;
   char line[NAMELEN_MAX];
   char *r;
   int i,ret,p;
   string str,s,n[3],name;
   stringList slist;
   projectList.clear();


   r = getProjectHome();
   if (r == NULL) 
   {
       MPR1("PROJECT_HOME is not defined\n");
       return -1;

   }
 
   name = r ;
   name = name + PROJECT_INFO; 
   
   f.open(name.c_str() ,fstream::in | fstream::out | fstream::app);

 //  cout << PROJECT_INFO <<endl;

   if (!f.fail())
   while (!f.eof()) 
   {
      f.getline(line,NAMELEN_MAX);  
      p = 0;
      str = line;
      if (str.empty()) continue;
      if (str.at(0) == '#') continue; 
      // cout << line<<endl;
      slist = splitStr(str);
      if (slist.size() < 3 ) continue;// name user date
  
      str = slist[0];
      if (!str.empty()) 
      {

         pi.set(slist[0],slist[1],slist[2]);
         projectList.push_back(pi);  
      }
      
   }//endof line
   f.close();
   if (projectList.size() == 0) 
   {
      return -2;
   }
   else
      return 0;
}
int projectMng::loadLines()
{
   fstream f;
   projectInfo pi;
   char line[NAMELEN_MAX];
   int i,ret,p;
   string str,s,n[3],name,project;
   stringList slist;
   lineList.clear();

   if (m_name.empty()) 
   {
      // log->warning(" No project selected!! %s %s  ","name = ", " ");
      return -1;
   }
   project = m_name;
   name = getProjectHome();
   name = name +PROJECT_LINE_INFO +project;
   
   f.open(name.c_str() ,fstream::in | fstream::out | fstream::app);

 //  cout << PROJECT_INFO <<endl;

   if (!f.fail())
   while (!f.eof()) 
   {
      f.getline(line,NAMELEN_MAX);  
      p = 0;
      str = line;
      if (str.empty()) continue;
      if (str.at(0) == '#') continue;
      // cout << line<<endl;
      slist = splitStr(str);
      if (slist.size() < 3 ) continue;// name user date
 
      str = slist[0];
      if (!str.empty()) 
      {
         pi.set(slist[0],slist[1],slist[2]);
         lineList.push_back(pi);
          
      }
      
   }//endof line
   f.close();

   if (lineList.size() == 0) 
   {
      return -1;
   }
   else
      return 0;
}

int projectMng::mkDir(const char *d)
{
    int i;
    //dir.setPath("");
    i = dir.mkpath(d);
    return i;
}
int projectMng::rmDir(const char *d)
{
    int i;
    QString str;
    str = d;
    dir.setPath(str);
    i = dir.removeRecursively();
    return i;

}
