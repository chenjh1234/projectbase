#ifndef COMFUN_H
#define COMFUN_H

//#include <stringlist>
using namespace std;
#include <sys/types.h>
#include <dirent.h>
//#include <regex.h>
 
#include <string>
#include <iostream>
#include <cmath>
#include <ctime>
#include <stdio.h>
#include <vector>
#include "sysdefine.h"
//#define MAX_STR 256
#define FIND_MODE 1
#include <QDir>
#include <QString>
#include <QFileInfo>

typedef vector< string> stringList;
/**
 * splt srings delimited by space(can be more space )to 
 * stringList 
 * 
 * @author cjh (8/25/2014)
 * 
 * @param str 
 * input str 
 * 
 * @return stringList 
 */
stringList splitStr(string str);
/**
 * merge the stringlist to string by add a space between 
 * strings. 
 * 
 * @author cjh (8/25/2014)
 * 
 * @param list 
 * 
 * @return string 
 */
string mergeStr(stringList list);
string toStr(int i);
string toStr(float i);
string toStr(double i);
/**
 * find files use "find -maxdepth 1"

 * @param ch : base path;
 * @param filter : like  "*.cpp"
 * 
 * @return stringList 
 */
stringList findFiles(char *ch, char *filter); // include all things :file,dir,ln
/**
 * 
 * use opendir readdir closedir
 * 
 * @param ch : base dir;
 * 
 * @return stringList 
 */
stringList dirFiles(char *ch);//files only
void dirFileAll(char *ch,stringList &strl);//files only
bool isPattern(char * str ,char *pattern);

#endif
