/*                    */

#include "logfile.h"

#include "sysdefine.h"


logFile::logFile( char const* filename ) : myFilename( filename ), myIsOpenedLocally(false) 
{
  if( myFilename != NULL ) 
  {
    myLogFile = fopen( myFilename, "a" );
    if( myLogFile == NULL )
    {
        cout <<"Can't open logfile: " << filename << endl;
        myFilename = NULL;
        myIsOpenedLocally = false;
        myLogFile = stdout;
    }
    else
       myIsOpenedLocally = true;
  }
  init();
}
logFile::logFile( FILE* file ) : myFilename( "Unknown" ), myIsOpenedLocally( false ) 
{
  myLogFile = file;
  init();
}
logFile::logFile() 
{
  myFilename = NULL;
  myIsOpenedLocally = false;
  myLogFile = stdout;
  init();
}
void logFile::init() 
{
  char *c;
  c = getUser();
  user = c;

}
//-----------------------------------------
logFile::~logFile() {
  if( myIsOpenedLocally && myLogFile ) 
  {
    fclose( myLogFile );
    myLogFile = NULL;
  }
}
//-----------------------------------------
void logFile::tline( char const* text, ... )
{
  if( myLogFile ) 
  {
    va_list argList;
    va_start( argList, text );
    fprintf( myLogFile, "%s %s: ", m_tm.cdate(),user.c_str());
    vfprintf( myLogFile, text, argList );
    fprintf( myLogFile, "\n" );
#ifdef CS_DEBUG
    fflush(myLogFile);
#endif
  }
}
//-----------------------------
//-----------------------------------------
void logFile::line( char const* text, ... )
{
  if( myLogFile ) 
  {
    va_list argList;
    va_start( argList, text );
    fprintf( myLogFile, "%s: ", user.c_str());
    vfprintf( myLogFile, text, argList );
    fprintf( myLogFile, "\n" );
#ifdef CS_DEBUG
    fflush(myLogFile);
#endif
  }
}
//-----------------------------------------
void logFile::write( char const* text, ... ) 
{
  if( myLogFile ) 
  {
    va_list argList;
    va_start( argList, text );
    vfprintf( myLogFile, text, argList );
  #ifdef CS_DEBUG
    fflush(myLogFile);
  #endif
  }
}
//-----------------------------------------
void logFile::error( char const* text, ... ) 
{
  if( myLogFile ) 
  {
    va_list argList;
    va_start( argList, text );
    fprintf( myLogFile, "FATAL ERROR:\n" );
    fprintf( myLogFile, "%s %s: ", m_tm.cdate(),user.c_str());
    vfprintf( myLogFile, text, argList );
    fprintf( myLogFile, "\n" );
  }
   
}
 
//-----------------------------------------
void logFile::warning( char const* text, ... ) 
{
  if( myLogFile ) {
    va_list argList;
    va_start( argList, text );
    fprintf( myLogFile, "WARNING:\n" );
    fprintf( myLogFile, "%s %s: ", m_tm.cdate(),user.c_str());
    vfprintf( myLogFile, text, argList );
    fprintf( myLogFile, "\n" );
  }
}
//-----------------------------------------
void logFile::flush() 
{
  if( myLogFile ) 
  {
    fflush(myLogFile);
  }
}



