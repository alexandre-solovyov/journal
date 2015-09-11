
#include <QApplication>
#include <QDir>
#include <JournalGUI_SimpleInputCard.h>
#include <JournalDM_Model.h>
#include <JournalDM_Exercise.h>
#include <time.h>

int main( int argc, char** argv )
{
  srand( time( 0 ) );

  QApplication anApp( argc, argv );

  // 1. Style setting
  QString aStylesPath = qgetenv( "STYLES_DIR" );
  QDir aStylesFolder( aStylesPath );
  QString aStylePath = aStylesFolder.absoluteFilePath( "JournalGUI.css" );
  QFile aFile( aStylePath );
  aFile.open( QFile::ReadOnly );
  QString aStyle = aFile.readAll();
  aFile.close();
  anApp.setStyleSheet( aStyle );

  // 2. Loading model
  QString aTestDataPath = qgetenv( "EXAMPLES_DIR" );
  QDir aTestDataFolder( aTestDataPath );
  QString aPath = aTestDataFolder.absoluteFilePath( "german.txt" );
  JournalDM_Model aModel;
  bool isOK = aModel.Load( aPath );
  JournalDM_ExerciseData aData = aModel.GetRandomExercise();

   // 3. Test exercise
  double phi = 1.61803398875;
  int h = 320;
  int w = ( int )( h * phi );

  JournalGUI_SimpleInputCard aWindow;
  aWindow.resize( w, h );
  aWindow.SetExercise( aData );
  aWindow.show();

  return anApp.exec();
}
