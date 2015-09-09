
/**
  @file
  \brief Implementation of the test application for the DHDF library
*/

#include <TestLib.h>
#include <TestLib_Runner.h>
#include <JournalDM_TestModel.h>
#include <QDir>

QString GetTestFile( const QString& theRelativePath )
{
  QString aTestDataPath = qgetenv( "TEST_DATA_DIR" );
  QDir aTestDataFolder( aTestDataPath );
  return aTestDataFolder.absoluteFilePath( theRelativePath );
}

const QString& operator << ( std::ostream& theStream, const QString& theLine )
{
  theStream << theLine.toStdString();
  return theLine;
}

/**
  The main function of the tests application
  @param argc the number of arguments
  @param argv the array of arguments
  @return the tests exit status
*/
int main( int argc, char **argv )
{
  TestLib_Runner aRunner;
  aRunner.addTest( JournalDM_TestModel::suite() );

  int aResult = TestLib_Run( argc, argv, "Journal", aRunner, "TEST_RESULTS_DIR",
                             "", "Journal.xml", "", "Journal.cfg" );

  return aResult;
}
