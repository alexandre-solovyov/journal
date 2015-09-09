
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

bool JournalDM_Tools::IsWord( const QString& theWord )
{
  for( int i=0, n=theWord.size(); i<n; i++ )
    if( !theWord[i].isLetter() )
      return false;
  return true;
}
