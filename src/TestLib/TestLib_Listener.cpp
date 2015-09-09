
/**
  @file
  \brief Implementation of the custom listener printing the time of test execution
*/

#include <TestLib_Listener.h>
#include <TestLib_PerformanceTest.h>
#include <cppunit/Test.h>
#include <iostream>

/**
  \brief Constructor
*/
TestLib_Listener::TestLib_Listener()
: myStart( 0 ), myComplete( 0 )
{
}

/**
  \brief Destructor
*/
TestLib_Listener::~TestLib_Listener()
{
}

/**
  \brief Clear the internal state of the listener
*/
void TestLib_Listener::Clear()
{
  myStart = 0;
  myComplete = 0;
}

/**
  Get complete time of all tests execution in milliseconds
  @return complete time in milliseconds
*/
INT64 TestLib_Listener::GetCompleteTimeInMS() const
{
  return myComplete;
}

/**
  Handler for test start
  @param theTest the started tests
*/
void TestLib_Listener::startTest( CppUnit::Test* theTest )
{
  std::string aName;
  if( theTest )
    aName = theTest->getName();

  std::cout << aName << "...";
  myStart = GetTimeForCurrentThreadInMs();
}

/**
  Handler for test finish
  @param theTest the finished tests
*/
void TestLib_Listener::endTest( CppUnit::Test* theTest )
{
  INT64 aCurTime = GetTimeForCurrentThreadInMs();
  INT64 anExecTimeMS = aCurTime - myStart;
  myComplete += anExecTimeMS;
  std::cout << " " << anExecTimeMS << " ms" << std::endl;
}

/**
  Handler for test suite start
  @param theTest the started test suite
*/
void TestLib_Listener::startSuite( CppUnit::Test* theTest )
{
}

/**
  Handler for test suite finish
  @param theTest the finished test suite
*/
void TestLib_Listener::endSuite( CppUnit::Test* theTest )
{
}

/**
  Handler for test failure
  @param theFailure the failure information
*/
void TestLib_Listener::addFailure( const CppUnit::TestFailure& theFailure )
{
}

