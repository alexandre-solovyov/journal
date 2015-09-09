
/**
  @file
  \brief Implementation of automatic tests for model loading
*/

#include <JournalDM_TestModel.h>
#include <JournalDM_Model.h>

void JournalDM_TestModel::test_loading()
{
  JournalDM_Model aModel;
  CPPUNIT_ASSERT_EQUAL( true, aModel.load( "" ) );
}
