
/**
  @file
  \brief Declaration of import/export specifications for classes
*/

#pragma once

#ifdef WIN32
  #ifdef TESTLIB_EXPORTS
    #define TESTLIBAPI __declspec(dllexport)   ///< the export declaration
  #else
    #define TESTLIBAPI __declspec(dllimport)   ///< the export declaration
  #endif
#else
  #define TESTLIBAPI   ///< the export declaration
#endif

typedef long long INT64;   ///< the cross-platform type definition for 64-bits integer

#include <string>
#include <fstream>
#include <sstream>

class TestLib_Runner;

int TESTLIBAPI TestLib_Run( int argc, char** argv, 
                            const std::string& theAppName,
                            TestLib_Runner& theRunner,
                            const std::string& theTestResultsVar,
                            const std::string& theRefTestResultsVar,
                            const std::string& theResultFileName,
                            const std::string& theReportStyleSheet,
                            const std::string& theConfigFile );

extern std::string TEST_RESULTS_PATH;
extern std::string REF_TEST_RESULTS_PATH;

