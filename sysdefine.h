#ifndef SYSDEFINE_H
#define SYSDEFINE_H

//#include <stringlist>
using namespace std;

#include <cstdlib>
#include <string>
#include <vector>
#include <fstream>
#include <QDebug>
#include <QString>

#define INSTALL_HOME "GEOSEIS" //envVAR of installation
//#define DATA_VERSION "1.01"
#define DATA_VERSION "1.11"//2018.12
#define DIR_CONFIG "config"
#define DIR_DOC "doc"
#define DIR_MOD "mod"
#define DIR_LIB "lib"
#define DIR_INCLUDE "include"

#ifdef WIN32
#define SLASH "\\"
#define PROJECT_INFO "\\.project.info"//project information: $PROJECT_HOME/.project.info
#define PROJECT_LINE_INFO "\\.PINFO_" //line information: $PROJECT_HOME/.PINFO_projectname
#define PROJECT_LOG "\\.project.log"  //logfile for system:$PROJECT_HOME/.project.log
#else
#define SLASH "/"
#define PROJECT_INFO "/.project.info"//project information: $PROJECT_HOME/.project.info
#define PROJECT_LINE_INFO "/.PINFO_" //line information: $PROJECT_HOME/.PINFO_projectname
#define PROJECT_LOG "/.project.log"  //logfile for system:$PROJECT_HOME/.project.log
#endif

#define PROJECT_HOME "PROJECT_HOME"  //envVAR  dir: contain project information files:

   


#define NAMELEN_MAX 256 

typedef vector< string> stringList;

#define MPR1(a) printf(a)
#define MPR2(a,b) printf(a,b)
#define MPR3(a,b,c) printf(a,b,c)
#define MPR4(a,b,c,d) printf(a,b,c,d)
#define MPR5(a,b,c,d,e) printf(a,b,c,d,e)

char * getInstallDir();
char * getConfigDir();
char * getDocDir();

char *getProjectDir();
char * getUser();
char * getHostname();
char * getHomeDir();
#endif
