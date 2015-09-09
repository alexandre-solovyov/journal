
/**
  @file
  \brief Implementation of the main function for tests running
*/

#include <TestLib.h>
#include <TestLib_Listener.h>
#include <TestLib_Runner.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/XmlOutputter.h>
#include <stdexcept>

#ifdef WIN32
  #include <direct.h>
#endif

std::string TEST_RESULTS_PATH;         ///< the path with test results
std::string REF_TEST_RESULTS_PATH;     ///< the path with reference test results

/**
  Get the value of an environment variable
  @param theVarName an environment variable's name
  @return the environment variable's value
*/
std::string GetEnv( const std::string& theVarName )
{
#ifdef WIN32
  char* aBuf;
  size_t aBufSize;
  _dupenv_s( &aBuf, &aBufSize, theVarName.c_str() );
  if( aBuf )
  {
    std::string aValue = aBuf;
    free( aBuf );
    return aValue;
  }
  else
    return "";
#else
  char* aVarValue = getenv( theVarName.c_str() );
  if( aVarValue )
    return aVarValue;
  else
    return "";
#endif
}

/**
  Make the directory if it does not existed
  @param thePath the path to the directory
  @return the state of creation
*/
bool MakeDir( const std::string& thePath )
{
#ifdef WIN32
  return !::_mkdir( thePath.c_str() );
#else
  return !mkdir( thePath.c_str(), 0777 );
#endif
}

/**
  The main function for the tests running
  @param argc the number of the command-line arguments
  @param argv the array of the command-line arguments
  @param theAppName the name of application to test
  @param theRunner the set of tests to run
  @param theTestResultsVar the environment variable for the tests results folder
  @param theRefTestResultsVar the environment variable for the reference tests results folder
  @param theResultFileName the base name (without extension) for the result file
  @param theReportStyleSheet the file of style sheet for the XML report
  @param theConfigFile the configuration file
  @return the tests final state: 0 -- all tests are passed; other values -- some error(s) appeared
*/
int TestLib_Run( int argc, char** argv, 
                 const std::string& theAppName,
                 TestLib_Runner& theRunner,
                 const std::string& theTestResultsVar,
                 const std::string& theRefTestResultsVar,
                 const std::string& theResultFileName,
                 const std::string& theReportStyleSheet,
                 const std::string& theConfigFile )
{
  std::string aResultFile;
  if( !theTestResultsVar.empty() )
    TEST_RESULTS_PATH = GetEnv( theTestResultsVar );

  if( !theRefTestResultsVar.empty() )
    REF_TEST_RESULTS_PATH = GetEnv( theRefTestResultsVar );

  if( !TEST_RESULTS_PATH.empty() )
  {
    MakeDir( TEST_RESULTS_PATH );
    aResultFile = TEST_RESULTS_PATH + "/" + theResultFileName;
  }

  if( !REF_TEST_RESULTS_PATH.empty() )
    MakeDir( REF_TEST_RESULTS_PATH );

  CPPUNIT_NS::TestResult aController;
  CPPUNIT_NS::TestResultCollector aResult;
  aController.addListener( &aResult );
  TestLib_Listener aCustomListener;
  aController.addListener( &aCustomListener );

  if( !theConfigFile.empty() )
  {
    std::string aConfigFile = TEST_RESULTS_PATH + "/" + theConfigFile;
    printf( "Using the tests configuration file: %s\n", aConfigFile.c_str() );
    theRunner.Load( aConfigFile );
  }

  try
  {
    CPPUNIT_NS::stdCOut() << "Running tests for " << theAppName << std::endl;
    theRunner.Run( aController );

    //CPPUNIT_NS::stdCOut() << "\n";

    std::cout << "Complete time: " << aCustomListener.GetCompleteTimeInMS() << " ms" << std::endl;

    CPPUNIT_NS::CompilerOutputter anOutputter( &aResult, CPPUNIT_NS::stdCOut() );
    anOutputter.write(); 

    if( !aResultFile.empty() )
    {
      std::ofstream aFile( aResultFile.c_str() );
      CPPUNIT_NS::XmlOutputter anXml( &aResult, aFile );
      if( !theReportStyleSheet.empty() )
        anXml.setStyleSheet( theReportStyleSheet );
      anXml.write();
      aFile.close();
    }
  }
  catch( std::invalid_argument& e )  // Test path not resolved
  {
    CPPUNIT_NS::stdCOut()  <<  "\n"  
                            <<  "ERROR: "  <<  e.what()
                            << "\n";
    return 1;
  }

  return aResult.wasSuccessful() ? 0 : 1;
}
