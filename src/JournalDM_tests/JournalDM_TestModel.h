
/**
  @file
  \brief Declaration of automatic tests for model loading
*/

#pragma once 

#include <cppunit/extensions/HelperMacros.h>

/**
  \class DHDF_TestParser 
  \brief Implementation of automatic tests for parser
*/
class JournalDM_TestModel : public CppUnit::TestCase
{ 
public: 
  ///@cond INTERNAL
  CPPUNIT_TEST_SUITE( JournalDM_TestModel );
  CPPUNIT_TEST( test_loading );
  CPPUNIT_TEST_SUITE_END();
  ///@endcond

public:
  void test_loading();
};
