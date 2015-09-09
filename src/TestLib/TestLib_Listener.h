
/**
  @file
  \brief Declaration of the custom listener printing the time of test execution
*/

#pragma once

#include <TestLib.h>
#include <cppunit/TestListener.h>

/**
  \class TestLib_Listener
  \brief Implementation of the custom listener printing the time of test execution
*/
class TestLib_Listener : public CppUnit::TestListener
{
public:
  TestLib_Listener();
  virtual ~TestLib_Listener();

  void Clear();
  INT64 GetCompleteTimeInMS() const;

  virtual void startTest( CppUnit::Test* ) override;
  virtual void endTest( CppUnit::Test* ) override;

  virtual void startSuite( CppUnit::Test* ) override;
  virtual void endSuite( CppUnit::Test* ) override;

  virtual void addFailure( const CppUnit::TestFailure& ) override;

private:
  INT64 myStart; ///< start time in milliseconds
  INT64 myComplete; ///< complete time of all tests execution in milliseconds
};

