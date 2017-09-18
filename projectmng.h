#ifndef PROJECTMNG_H
#define PROJECTMNG_H

 
using namespace std;
#include <stdio.h>
#include <stdlib.h>
#include "sysdefine.h"
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "dtime.h"
#include "logfile.h"
#include "comfun.h"
#include "diskmng.h"
#include "sysdefine.h"
#include <QDir>
#include <QDebug>

             // project line names
//#define DATADIRS 5
#define DIRS  {(char*)"flow",(char*)"job",(char*)"data",(char*)"log",(char*)"table",NULL}

 
/**
 * 
 * 
 * @author cjh (8/25/2014)
 */

 
/**
 * project information :
 *  
 * also the line informations 
 * 
 * @author cjh (8/25/2014)
 */
class projectInfo
{
public:

   projectInfo(){set("1","2","3");};
   projectInfo(string n,string u,string d)
   {
      set(n,u,d);
   }
   string name,user,date;
   int set(string name1,string user1,string date1)
   {
      name = name1;
      user = user1;
      date = date1;
      m_map["name"] = flexVar(name);
      m_map["user"] = flexVar(user);
      m_map["date"] = flexVar(date);
      return 0;
   };
   map <string ,flexVar> m_map;
};
typedef vector< projectInfo > PROJECTList;
typedef vector< projectInfo > LINEList;

/** 
 * projact manager: 
 *  
 * all project info in the system :$PROJECT_HOME/.project.info :
 *   projectname username  create date&time. 
 *  
 * project log for system :$PROJECT_HOME/.project.log 
 *   log for: create,remove :project lines;
 *  
 * line informatin in a project:$PROJECT_HOME/.PINFO_projectname
 *   linename username  date&time 
 * 
 * @author cjh (8/25/2014)
 */
  

class projectMng
{
public:
   projectMng();
   projectMng(char * name);
   ~projectMng();
 /**
   *  name of the project
   */
   int init();
   int setProject(char * name);
   string getCurrentProject() ;
   int setLine(char * name);
   string getCurrentLine();
   int createProject(char * name);
   int createLine(char *l);
   bool isProjectExist(char *name);
   bool isLineExist(char *line);
   char *getProjectHome();// move to comfun

   string getLineHome(char *l);
   string getProjectHome(char *p);
  
   int numProjects();
   int numLines();
   int getDiskList();
   PROJECTList getProjectList();
   LINEList getLineList();
 
   int removeProject(char *);
   int removeLine(char *);

   int createDirs(char *);
   int mkDir(const char *);// mkdir from "/";
   int rmDir(const char *);//rmdir and all its subdir  files
   //int removeDirs(char *);
   // we donot need remove dirs,becaouse ,when remove line(project) ,it will remove everything.
 
   dtime tm;
   QDir dir;

private:
   int loadProjects();
   int saveProjects();
   int loadLines();
   int saveLines();
   int createProjectDirs(char *name);
   int createLineDirs(char *name);
   int removeProjectDirs(char *name);
   int removeLineDirs(char *name);
    
   
    
/**
 * number of projects in the system;
 */ 
   string m_name,m_line;

   bool m_bExist;  
   LINEList lineList;
   stringList diskList,dirList;
   PROJECTList projectList;
   logFile *log;
   dtime m_tm;



};

 
#endif

