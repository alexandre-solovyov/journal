
#include <QApplication>
#include <JournalGUI_Window.h>

int main( int argc, char** argv )
{
  QApplication anApp( argc, argv );

  double phi = 1.61803398875;
  int h = 320;
  int w = ( int )( h * phi );

  JournalGUI_Window aWindow;
  aWindow.resize( w, h );
  aWindow.show();

  return anApp.exec();
}
