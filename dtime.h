#ifndef DTIME_H
#define DTIME_H

using namespace std;

#include <sys/time.h>
#include <string>
#include <stdio.h>


/**
 * 
 * get the date and time,for loging
 * @author cjh (8/25/2014) 
 * cdate: 
 * sprintf(text,"%4d-%02d-%02d_%02d:%02d:%02d "
                , year,month,day, hour,min,sec); 
 */
class dtime
{
public:
   dtime();
   ~dtime();
    /**
     * 
     * 
     * @author cjh (8/25/2014)
     * 
     * @return char*  the format like: 2014-08-02_22:27:59
     */
    char * cdate() ;
    char * ddate(time_t t) ;
///  start to counter:
    void start();
/// @return elapsed time in seconds from start()
    double getElapsedTime();   
  
 

private:
   void UNIXsec2date( int& year, int& month, int& day, int& hour, int& min, int& sec, int unixSec ) ;
   char text[30];

   struct timeval tStart;
   struct timeval tEnd;
/// Subtract two timeval objects. Return time difference in seconds
   double timeval_subtract( struct timeval* tStart, struct timeval* tEnd );
 
};
#endif

