
/**
  @file
  \brief Declaration of functions and macros for the performance tests
*/

#pragma once

#include <TestLib.h>
#include <string>

const std::string PERFORMANCE_INFO = 
  "The performance of '%s' in '%s':\n"
  "  expected maximum: %.3lf ms\n"
  "  actual:           %.3lf ms\n";   ///< the pattern for the performance test information

#ifdef _DEBUG
  const bool IS_DEBUG = true;         ///< if the debug mode is active
  const std::string MODE = "debug";   ///< the string representation of the mode
#else
  const bool IS_DEBUG = false;        ///< if the debug mode is active
  const std::string MODE = "release"; ///< the string representation of the mode
#endif

void TESTLIBAPI DeletePerformanceInfo( const std::string& theFilePrefix );

void TESTLIBAPI WritePerformanceInfo( const std::string& theFilePrefix,
                                      const std::string& theCase,
                                      double theTimeMs,  
                                      double theMaxTimeMs );

INT64 TESTLIBAPI GetTimeForCurrentThreadInMs();
INT64 TESTLIBAPI GetTimeOfDayInMs();

/**
  Macro for the declaration of a performance test
  @param theCount how many times the test should be performed
*/
#define PERFORMANCE_TEST( theCount )                                          \
    {                                                                          \
      INT64 aStartMs = GetTimeForCurrentThreadInMs();                         \
                                                                              \
      int n = (theCount);                                                     \
      for( int i=0; i<n; i++ )                                                \
      {                                                                       \


/**
  Macro for the final assertion about the time of one iteration of the performance test
  @param theLogFilePrefix the log file prefix
  @param theTestMethod the name of the test case
  @param theMaxTimeInDebugMs the maximal expected time in the debug mode
  @param theMaxTimeInReleaseMs the maximal expected time in the release mode
*/
#define ASSERT_PERFORMANCE( theLogFilePrefix,                                         \
                            theTestMethod,                                            \
                            theMaxTimeInDebugMs,                                      \
                            theMaxTimeInReleaseMs )                                   \
      }                                                                               \
      INT64 anEndMs = GetTimeForCurrentThreadInMs();                                  \
      double aTimeMs = ( anEndMs - aStartMs ) * 1.0 / n;                              \
      double aMaxTimeMs = IS_DEBUG ?                                                  \
        theMaxTimeInDebugMs : theMaxTimeInReleaseMs;                                  \
      WritePerformanceInfo( theLogFilePrefix, theTestMethod, aTimeMs, aMaxTimeMs );   \
      if( aTimeMs > aMaxTimeMs )                                                      \
      {                                                                               \
        const int BUF_LEN = 1024;                                                     \
        char aMsg[BUF_LEN];                                                           \
        sprintf( aMsg, PERFORMANCE_INFO.c_str(), theTestMethod,                       \
          MODE.c_str(), aMaxTimeMs, aTimeMs );                                        \
        CPPUNIT_FAIL( aMsg );                                                         \
      }                                                                               \
    }                                                                                  \

