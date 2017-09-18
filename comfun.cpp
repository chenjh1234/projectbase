#include "comfun.h"

stringList splitStr(string str)
{
   int len,p,ret;
   string s;
   stringList slist;
   len = str.length();
   
   p = 0;
   while (1)
   {
    
      while (str[p] == ' ')//erase " "
          p++;

      ret = str.find(" ",p);
      if (ret != string::npos) 
      {
      
         s = str.substr(p,ret-p);
         slist.push_back(s);
         p =ret +1;
         //if ( p >= len-1) break;//2014.8.27
         if ( p >= len) break;
      }
      else
      {
         s = str.substr(p);
         slist.push_back(s);
         break;

      }
       
   }
   return slist;
      
}
string mergeStr(stringList slist)
{
   int len,i;
   string s;
   len = slist.size();
   
   for (i = 0 ;i< len ;i++) 
   {
      s = s + slist[i] + " ";
   } 
   return s;
}
string toStr(int id)
{
    string str;
    char ch[NAMELEN_MAX];

    sprintf(ch,"%d",id);
    str= ch;
    return str;
}
string toStr(float id)
{
    string str;
    char ch[NAMELEN_MAX];

    sprintf(ch,"%f",id);
    str= ch;
    return str;
}
string toStr(double id)
{
    string str;
    char ch[NAMELEN_MAX];

    sprintf(ch,"%f",id);
    str= ch;
    return str;
}
/**
 * use "find ch -maxdepth 1 -name filter "command 
 * list files in "ch" dirctory donot include sub directory; 
 * include the director name; 
 * 
 * @author cjh (9/10/2014)
 * 
 * @param ch 
 * @param filter 
 * 
 * @return stringList 
 */
stringList findFiles(char *ch,char *filter)
{
    int num,i;
    QString qstr,path,qfilter;
    QDir dir;
    QFileInfoList flist;  
    QStringList qlist;

    string str;
    stringList  strlist;
  
    path = ch;
    qfilter = filter;
    qlist << qfilter;

    dir.setPath(ch);
    flist = dir.entryInfoList(qlist);
    num = flist.size();
    for (i =0; i<num; i++)
    {
        if(flist[i].isDir()) continue;
        qstr = flist[i].filePath();
        str = qstr.toUtf8().data();
        strlist.push_back(str);
    }
    return strlist;

}
  
/**
 * list all files in the drectory,incluide the subdirectory; 
 * use opendir() 
 * 
 * 
 * 
 * @param ch 
 * @param strlist 
 */
void  dirFileAll(char *ch,stringList &strlist)
{
     int num,i;
    QString qstr,path,qfilter;
    QDir dir;
    QFileInfoList flist;  
    QStringList qlist;

    string str;
    //stringList  strlist;
    path = ch;
    qfilter = "*.*";
    qlist << qfilter;

    dir.setPath(ch);
    flist = dir.entryInfoList(qlist);
    num = flist.size();
    for (i =0; i<num; i++)
    {
 
        qstr = flist[i].filePath();
        str = qstr.toUtf8().data();
        if(flist[i].isDir())
        {
            dirFileAll( qstr.toUtf8().data(),strlist);
        }
        strlist.push_back(str);
    }
    return ;
}
/**
 * list files only in this directory;notinclude the dirctory 
 * names 
 * 

 * @param ch 
 * 
 * @return stringList 
 */
stringList dirFiles(char *ch)
{
    return findFiles(ch,"*");
}
 
/**
 * if(isPattern((char *)"123",(char *)"1*")) 
 * test if buf(string)  in the pattern(wild*)
 * 
 *
 * @param buf 
 * @param pattern 
 * 
 * @return bool 
 */
bool isPattern(char * buf ,char *pattern)
{
    int i,z,cflags;
    string str;
    QDir dir;
    QString filter,fname;
    filter = QString(pattern);
    fname = QString(buf);
    return  dir.match(filter,fname);
}
 
