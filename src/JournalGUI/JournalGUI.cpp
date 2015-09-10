
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

  QString aTestDataPath = qgetenv( "EXAMPLES_DIR" );
  QDir aTestDataFolder( aTestDataPath );
  QString aPath = aTestDataFolder.absoluteFilePath( "german.txt" );
  JournalDM_Model aModel;
  bool isOK = aModel.Load( aPath );
  JournalDM_ExerciseData aData = aModel.GetRandomExercise();

  double phi = 1.61803398875;
  int h = 320;
  int w = ( int )( h * phi );

  JournalGUI_SimpleInputCard aWindow;
  aWindow.resize( w, h );
  aWindow.SetExercise( aData );
  aWindow.show();

  return anApp.exec();
}
