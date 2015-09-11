
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

QString JournalDM_Tools::Hex( int theNumber, int theMinLength )
{
  QString aHex = QString::number( theNumber, 16 );
  while( aHex.length() < theMinLength )
    aHex = "0" + aHex;
  return aHex;
}

QString JournalDM_Tools::ColorToHex( const QColor& theColor )
{
  QString aColorRepr = Hex( theColor.red() ) + 
                       Hex( theColor.green() ) + 
                       Hex( theColor.blue() );
  return aColorRepr;
}
