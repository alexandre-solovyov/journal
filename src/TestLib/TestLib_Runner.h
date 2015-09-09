
/**
  @file
  \brief Declaration of the custom runner allowing start a subset of tests
*/

#pragma once

#include <TestLib.h>
#include <cppunit/TestRunner.h>
#include <list>

#ifdef WIN32
  #pragma warning( disable: 4251 )
  #pragma warning( disable: 4275 )
#endif

/**
  \class TestLib_Runner
  \brief Implementation of the custom runner allowing start a subset of tests
*/
class TESTLIBAPI TestLib_Runner : public CPPUNIT_NS::TestRunner
{
public:
  void Add( const std::string& theSubstr );
  bool Load( const std::string& theConfigFile );
  void Run( CPPUNIT_NS::TestResult& theController );

protected:
  void GetTests( CPPUNIT_NS::Test* theRoot, std::list<std::string>& theAllowedTests ) const;
  bool IsAllowed( const std::string& theTestName ) const;

private:
  std::list<std::string> mySubStrings; ///< the list of substring patterns 
};

#ifdef WIN32
  #pragma warning( default: 4251 )
  #pragma warning( default: 4275 )
#endif

