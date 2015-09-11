
#include <QApplication>
#include <QDir>
#include <JournalGUI_SimpleInputCard.h>
#include <JournalGUI_ExerciseManager.h>
#include <JournalDM_Model.h>
#include <JournalDM_Exercise.h>

int main( int argc, char** argv )
{
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

   // 3. Test exercise
  JournalGUI_SimpleInputCard aWindow;
  JournalGUI_ExerciseManager aMgr( &aModel );
  aMgr.RandomExerciseOn( &aWindow );
  
  return anApp.exec();
}
