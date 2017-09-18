 
#ifndef LOGFILE_H
#define LOGFILE_H

using namespace std;

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <fstream>
#include <stdarg.h>
#include <iostream>
#include "dtime.h"
/**
 
    logFile log;
    log.tline("12345\n");
    logFile loga("123.log");
    log1.line("12344");
    log1.line("myline = %d,%s",i,s);
    
    line: user: + test +\n
    tline:time + user :test +\n;
    write: test
    error:"FATAL ERROR:\n" +tline
    warning:"WARNING:\n" +tline
 
*/
 
class logFile {
public:
  /**
   * Constructor
   * Pass NULL if no log information shall be output.
   * @param filename File name with full path where log information shall be written to
   */
  logFile( char const* filename );
  /**
   * Constructor 
   * Pass NULL if no log information shall be output.
   * @param file File stream where log information shall be written to
   */
  logFile( std::FILE* file );
  /**
   * Default constructor
   * Use this constructor to output to standard output
   */
  logFile();
  ~logFile();
  void init();
  /**
  * Print message line to log file, with terminating newline, similar to printf("...\n") 
  * time user: test 
  */
  void line( char const* text, ... );
  void tline( char const* text, ... );
  /**
  * Print message line to log file, without terminating newline, similar to printf("...") 
  * test 
  */
  void write( char const* text, ... );
  /**
  * Write error message to log file +\n
  * The message is formatted in a standard way to inform users that an error occurred 
  * FATAL ERROR: 
  * time user: test   
  */
  void error( char const* text, ... );
  
  /**
  * Write warning message to log file
  * The message is formatted in a standard way to inform users that a warning occurred 
  * WARNING: 
  * time user: test  
  *  
  */
  void warning( char const* text, ... );
  /**
  * Flush output
  */
  void flush();
  /**
  * @return file object
  */
  FILE* getFile() 
  {
    return myLogFile;
  }
  char * getFilename() 
  {
    return (char *)myFilename;
  }
private:
  logFile( logFile const& obj );
  std::FILE* myLogFile;
  char const* myFilename;
  /// true if file is opened within class. If yes then the file srtream will be closed during object destruction
  bool myIsOpenedLocally;
  dtime m_tm;
  string user;
};
  
 
#endif

