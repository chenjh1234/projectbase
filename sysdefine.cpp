#include "sysdefine.h"
char* getProjectDir()
{
   char * pPath;
   pPath = NULL;
   pPath = getenv(PROJECT_HOME);
   if (pPath == NULL) 
   {
       pPath = getHomeDir();
   }
   //qDebug() << "Project dir ==" << pPath;
   return pPath; 

}
char * getInstallDir()
{
    return getenv(INSTALL_HOME);
}
char * getConfigDir()
{
    //char *ch;
    static char cc[NAMELEN_MAX];
    string dir;    

    if (getInstallDir() == NULL) return NULL;

    dir = string(getInstallDir());
    dir = dir + SLASH + DIR_CONFIG;
    //ch = new char[dir.length()+1];
    memcpy(cc,(char *) dir.c_str(),dir.length());
    cc[dir.length()] =0;
    return cc;
}
char * getDocDir()
{
    //char *ch;
    static char cc[NAMELEN_MAX];
    string dir;
    //qDebug() << "111222";
    if (getInstallDir()== NULL ) return NULL;
    //qDebug() << "111222333";
 
    dir = string(getInstallDir());
    if (dir.empty()) return NULL;

    dir = dir + SLASH + DIR_DOC;
    //ch = new char[dir.length()+1];
    memcpy(cc,(char *) dir.c_str(),dir.length());
    cc[dir.length()] =0;
    return cc;
}
char * getUser()
{
#ifdef WIN32
    return getenv("USERNAME");
#else
    return getenv("USER");
#endif
}
char * getHomeDir()
{
    //qDebug() << "home=" << getenv("HOME");
    char *ch,*ch1;
    static char cc[NAMELEN_MAX];
    string str;
    ch  =  getenv("HOME");//linux, xp
    if (ch == NULL)
    {
        ch =  getenv("HOMEDRIVE");
        ch1 =  getenv("HOMEPATH");
        str = string(ch) + string(ch1);

        ch1 = (char *)str.c_str();
        memcpy(cc,ch1,str.length());
        cc[str.length()] = 0;
        return cc;
    }
    else
        return ch;
}
char * getHostname()
{
#ifdef WIN32
    return getenv("COMPUTERNAME");
#else
    
    return getenv("HOSTNAME");
#endif
    
}
