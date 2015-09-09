
/**
  @file
  \brief Implementation of the custom runner allowing start a subset of tests
*/

#include <TestLib_Runner.h>
#include <cppunit/TestPath.h>
#include <cppunit/TestResult.h>
#include <algorithm>
#include <fstream>

/**
  Conversion of the given string to lower-case
  @param theStr the string to convert to lower-case
  @return the converted string
*/
std::string ToLower( const std::string& theStr )
{
  std::string aStr = theStr;
  std::transform( aStr.begin(), aStr.end(), aStr.begin(), ::tolower );
  return aStr;
}

/**
  Add a substring pattern to test runner
  @param theSubstr the substring pattern to add
*/
void TestLib_Runner::Add( const std::string& theSubstr )
{
  mySubStrings.push_back( ToLower( theSubstr ) );
}

/**
  Load the configuration file with substring patterns
  @param theConfigFile the path to the configuration file
  @return if the operation is successful
*/
bool TestLib_Runner::Load( const std::string& theConfigFile )
{
  std::ifstream anInput( theConfigFile.c_str() );
  bool isOK = anInput.is_open();
  if( !isOK )
    return false;

  std::string aLine;
  while( std::getline( anInput, aLine ) )
  {
    int aPos = aLine.find( "//" );
    if( aPos != std::string::npos )
      aLine.erase( aPos );

    //trim 
    aLine.erase( 0, aLine.find_first_not_of( ' ' ) );
    aLine.erase( aLine.find_last_not_of( ' ' ) + 1 );

    if( !aLine.empty() )
      Add( aLine );
  }

  return true;
}

/**
  Determine if the given test name is allowed by patterns
  @param theTestName the test name
  @return true if the test name is allowed
*/
bool TestLib_Runner::IsAllowed( const std::string& theTestName ) const
{
  if( mySubStrings.empty() )
    return true;

  std::string aTestName = ToLower( theTestName );

  std::list<std::string>::const_iterator anIt = mySubStrings.begin(), aLast = mySubStrings.end();
  for( ; anIt!=aLast; ++anIt )
    if( aTestName.find( *anIt ) != std::string::npos )
      return true;

  return false;
}


/**
  Determine list of tests allowed by patterns from the given CPPUnit tests tree
  @param theRoot the root of the CPPUnit tests tree
  @param theAllowedTests the returned vector of allowed tests names
*/
void TestLib_Runner::GetTests( CPPUNIT_NS::Test* theRoot, std::list<std::string>& theAllowedTests ) const
{
  for( int i=0, n=theRoot->getChildTestCount(); i<n; i++ )
  {
    CPPUNIT_NS::Test* aTest = theRoot->getChildTestAt( i );
    std::string aName = aTest->getName();
    if( IsAllowed( aName ) )
      theAllowedTests.push_back( aName );
    else
      GetTests( aTest, theAllowedTests );
  }
}

/**
  Run all necessary tests
  @param theController the controller of the tests results
*/
void TestLib_Runner::Run( CPPUNIT_NS::TestResult& theController )
{
  std::list<std::string> aTests;
  GetTests( m_suite, aTests );
  std::list<std::string>::const_iterator anIt = aTests.begin(), aLast = aTests.end();
  for( ; anIt!=aLast; ++anIt )
  {
    std::string aTestPath = *anIt;
    CPPUNIT_NS::TestPath aPath = m_suite->resolveTestPath( aTestPath );
    CPPUNIT_NS::Test* aTest = aPath.getChildTest();
    theController.runTest( aTest );
  }
}

