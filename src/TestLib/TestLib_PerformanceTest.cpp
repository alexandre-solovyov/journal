
/**
  @file
  \brief Implementation of functions for the performance tests
*/

#include <TestLib_PerformanceTest.h>
#include <stdio.h>

#ifdef WIN32
  #include <windows.h>
#else
  #include <sys/time.h>
#endif

const std::string PERFORMANCE_LOG_FILE = "Performance.log";  ///< the default suffix for the performance log files

/**
  Delete the file with performance information
  @param theFilePrefix the file name prefix
*/
void DeletePerformanceInfo( const std::string& theFilePrefix )
{
  std::string aFileName = theFilePrefix + PERFORMANCE_LOG_FILE;
  std::remove( aFileName.c_str() );
}

/**
  Write information about the performance tests to log
  @param theFilePrefix the log file prefix
  @param theCase the name of the test case
  @param theTimeMs the actual time in milliseconds
  @param theMaxTimeMs the maximal expected time in milliseconds
*/
void WritePerformanceInfo( const std::string& theFilePrefix,
                           const std::string& theCase,
                           double theTimeMs,
                           double theMaxTimeMs )
{
  std::string aFileName = theFilePrefix + PERFORMANCE_LOG_FILE;
  const int BUF_LEN = 1024;
  char aMsg[BUF_LEN];
  sprintf( aMsg,
    "\n"
    "  case '%s':\n"
    "    mode: %s\n"
    "    expected maximal time: %6.4lf ms\n"
    "    actual time:           %6.4lf ms\n  \n",
    theCase.c_str(), MODE.c_str(), theMaxTimeMs, theTimeMs );
  FILE* aFile = fopen( aFileName.c_str(), "a" );
  fprintf( aFile, "%s", aMsg );
  fclose( aFile );
}

#ifdef WIN32
/**
  Convert the given time structure to milliseconds number
  @param theTime the time structure to convert
  @return the calculated number of milliseconds
*/
INT64 GetMilliseconds( const FILETIME& theTime )
{
  SYSTEMTIME aTime;
  FileTimeToSystemTime( &theTime, &aTime );
  INT64 aRes = 0;
  aRes += aTime.wHour * ( 3600 * 1000 );
  aRes += aTime.wMinute * ( 60 * 1000 );
  aRes += aTime.wSecond * ( 1000 );
  aRes += aTime.wMilliseconds;
  return aRes;
}
#endif

/**
  Calculate the complete execution time for the current thread 
  @return the calculated time as the number of milliseconds
*/
INT64 GetTimeForCurrentThreadInMs()
{
#ifdef WIN32
  FILETIME aCreationTime, anExitTime, aKernelTime, aUserTime;
  GetThreadTimes( GetCurrentThread(), &aCreationTime, &anExitTime, &aKernelTime, &aUserTime );
  INT64 aKernelMs = GetMilliseconds( aKernelTime );
  INT64 aUserMs = GetMilliseconds( aUserTime );
  return aKernelMs + aUserMs;
#else
  struct timespec aTime;
  clock_gettime( CLOCK_MONOTONIC, &aTime );
  INT64 aSec = aTime.tv_sec;
  aSec *= 1000;
  aSec += aTime.tv_nsec / 1000000;
  return aSec;
#endif
}

/**
 Get current day's time in milliseconds
 @return the current day's time in milliseconds
*/
INT64 GetTimeOfDayInMs()
{
#ifdef WIN32
 SYSTEMTIME aTime;
 GetSystemTime( &aTime );
 INT64 aRes = 0;
 aRes += aTime.wHour * ( 3600 * 1000 );
 aRes += aTime.wMinute * ( 60 * 1000 );
 aRes += aTime.wSecond * ( 1000 );
 aRes += aTime.wMilliseconds;
 return aRes;
#else
 struct timeval aTime;
 gettimeofday( &aTime, NULL );
 INT64 aRes = 0;
 aRes += aTime.tv_sec * 1000;
 aRes += aTime.tv_usec / 1000;
 return aRes;
#endif
}
