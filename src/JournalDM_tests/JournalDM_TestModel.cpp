
/**
  @file
  \brief Implementation of automatic tests for model loading
*/

#include <JournalDM_Tests.h>
#include <JournalDM_TestModel.h>
#include <JournalDM_Category.h>
#include <JournalDM_Model.h>
#include <JournalDM_Tools.h>
#include <JournalDM_TranslationParser.h>

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
  CPPUNIT_ASSERT_EQUAL( 8, aModel.GetCategory( 0 )->GetNbLines() );
  CPPUNIT_ASSERT_EQUAL( 6, aModel.GetCategory( 0 )->GetNbLines( true ) );
  CPPUNIT_ASSERT_EQUAL( 11, aModel.GetCategory( 0 )->GetNbExercises() );

  e = aModel.GetCategory( 0 )->GetExercise( 0 );
  CPPUNIT_ASSERT_EQUAL( QString( "couper ... pomme en deux parties" ), e.Question );
  CPPUNIT_ASSERT_EQUAL( QString( "une" ), e.Answer );

  e = aModel.GetCategory( 0 )->GetExercise( 3 );
  CPPUNIT_ASSERT_EQUAL( QString( "un poste = ..." ), e.Question );
  CPPUNIT_ASSERT_EQUAL( QString::fromUtf8( "должность" ), e.Answer );

  e = aModel.GetCategory( 0 )->GetExercise( 6 );
  CPPUNIT_ASSERT_EQUAL( QString( "aider ... qn" ), e.Question );
  CPPUNIT_ASSERT_EQUAL( QString( "" ), e.Answer );

  e = aModel.GetCategory( 0 )->GetExercise( 9 );
  CPPUNIT_ASSERT_EQUAL( QString::fromUtf8( "... = яблоко" ), e.Question );
  CPPUNIT_ASSERT_EQUAL( QString( "une pomme" ), e.Answer );

  e = aModel.GetCategory( 0 )->GetExercise( 10 );
  CPPUNIT_ASSERT_EQUAL( QString( "une pomme = ..." ), e.Question );
  CPPUNIT_ASSERT_EQUAL( QString::fromUtf8( "яблоко" ), e.Answer );
}

void JournalDM_TestModel::test_loading_folder()
{
  JournalDM_Model aModel;
  QString aPath = GetTestFile( "" );

  CPPUNIT_ASSERT_EQUAL( true, aModel.Load( aPath ) );
  CPPUNIT_ASSERT_EQUAL( 2, aModel.GetNbCategories() );
  CPPUNIT_ASSERT_EQUAL( QString( "test1" ), aModel.GetCategory( 0 )->GetName() );
  CPPUNIT_ASSERT_EQUAL( 8, aModel.GetCategory( 0 )->GetNbLines() );
  CPPUNIT_ASSERT_EQUAL( 6, aModel.GetCategory( 0 )->GetNbLines( true ) );
  CPPUNIT_ASSERT_EQUAL( 11, aModel.GetCategory( 0 )->GetNbExercises() );
  CPPUNIT_ASSERT_EQUAL( QString( "test2" ), aModel.GetCategory( 1 )->GetName() );
  CPPUNIT_ASSERT_EQUAL( 0, aModel.GetCategory( 1 )->GetNbLines() );
  CPPUNIT_ASSERT_EQUAL( 0, aModel.GetCategory( 1 )->GetNbLines( true ) );
  CPPUNIT_ASSERT_EQUAL( 0, aModel.GetCategory( 1 )->GetNbExercises() );
}

void JournalDM_TestModel::test_translation_parser()
{
  JournalDM_TranslationParser aParser( 0 );
  JournalDM_ExerciseList aResult;
  bool isBlock;
  
  aResult = aParser.extractData( "a = b", isBlock );
  CPPUNIT_ASSERT_EQUAL( 2, aResult.size() );
  CPPUNIT_ASSERT_EQUAL( QString( "... = b" ), aResult[0].Question );
  CPPUNIT_ASSERT_EQUAL( QString( "a" ), aResult[0].Answer );

  aResult = aParser.extractData( "a != b", isBlock );
  CPPUNIT_ASSERT_EQUAL( 0, aResult.size() );
}
