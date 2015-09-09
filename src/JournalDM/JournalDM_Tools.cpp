
#include <JournalDM_Tools.h>
#include <JournalDM_Constants.h>
#include <QStringList>

QString JournalDM_Tools::RemoveComments( const QString& theLine )
{
  QString aLine = theLine;
  foreach( QString aComment, COMMENTS )
  {
    while( true )
    {
      int anIndex = aLine.indexOf( aComment );
      if( anIndex>=0 )
        aLine = aLine.left( anIndex );
      else
        break;
    }
  }
  
  return aLine;
}
