
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
  CPPUNIT_TEST( test_remove_comments );
  CPPUNIT_TEST( test_loading_file );
  CPPUNIT_TEST( test_loading_folder );
  CPPUNIT_TEST_SUITE_END();
  ///@endcond

public:
  void test_remove_comments();
  void test_loading_file();
  void test_loading_folder();
};
