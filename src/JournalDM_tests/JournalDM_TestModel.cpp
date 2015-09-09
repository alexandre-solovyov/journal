
/**
  @file
  \brief Implementation of automatic tests for model loading
*/

#include <JournalDM_Tests.h>
#include <JournalDM_TestModel.h>
#include <JournalDM_Category.h>
#include <JournalDM_Model.h>
#include <JournalDM_Tools.h>

void JournalDM_TestModel::test_remove_comments()
{
  CPPUNIT_ASSERT_EQUAL( QString( "" ), JournalDM_Tools::RemoveComments( "" ) );
  CPPUNIT_ASSERT_EQUAL( QString( "abc" ), JournalDM_Tools::RemoveComments( "abc" ) );
  CPPUNIT_ASSERT_EQUAL( QString( "abc " ), JournalDM_Tools::RemoveComments( "abc //comment" ) );
  CPPUNIT_ASSERT_EQUAL( QString( "abc " ), JournalDM_Tools::RemoveComments( "abc //" ) );
  CPPUNIT_ASSERT_EQUAL( QString( "abc " ), JournalDM_Tools::RemoveComments( "abc // c1 //c2" ) );
  CPPUNIT_ASSERT_EQUAL( QString( "" ), JournalDM_Tools::RemoveComments( "//comment" ) );
  CPPUNIT_ASSERT_EQUAL( QString( "abc " ), JournalDM_Tools::RemoveComments( "abc #comment" ) );
  CPPUNIT_ASSERT_EQUAL( QString( "abc " ), JournalDM_Tools::RemoveComments( "abc #" ) );
  CPPUNIT_ASSERT_EQUAL( QString( "abc " ), JournalDM_Tools::RemoveComments( "abc # c1 #c2" ) );
  CPPUNIT_ASSERT_EQUAL( QString( "" ), JournalDM_Tools::RemoveComments( "#comment" ) );
  CPPUNIT_ASSERT_EQUAL( QString( "abc " ), JournalDM_Tools::RemoveComments( "abc # c2 // C1" ) );
}

void JournalDM_TestModel::test_loading_file()
{
  JournalDM_Model aModel;
  QString aFile = GetTestFile( "test1.txt" );
  JournalDM_ExerciseData e;

  CPPUNIT_ASSERT_EQUAL( true, aModel.Load( aFile ) );
  CPPUNIT_ASSERT_EQUAL( 1, aModel.GetNbCategories() );
  CPPUNIT_ASSERT_EQUAL( QString( "test1" ), aModel.GetCategory( 0 )->GetName() );
  CPPUNIT_ASSERT_EQUAL( 7, aModel.GetCategory( 0 )->GetNbLines() );
  CPPUNIT_ASSERT_EQUAL( 5, aModel.GetCategory( 0 )->GetNbExercises() );

  e = aModel.GetCategory( 0 )->GetExercise( 3 );
  CPPUNIT_ASSERT_EQUAL( QString::fromUtf8( "... poste = почта" ), e.Question );
  CPPUNIT_ASSERT_EQUAL( QString( "une" ), e.Answer );

  e = aModel.GetCategory( 0 )->GetExercise( 4 );
  CPPUNIT_ASSERT_EQUAL( QString( "aider ... qn" ), e.Question );
  CPPUNIT_ASSERT_EQUAL( QString( "" ), e.Answer );
}

void JournalDM_TestModel::test_loading_folder()
{
  ///< \todo
}

