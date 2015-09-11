
#pragma once

#include <JournalDM.h>
#include <QString>
#include <QColor>

class JOURNAL_DM_API JournalDM_Tools
{
public:
  static QString RemoveComments( const QString& );
  static bool IsWord( const QString& theWord );
  static QString Hex( int theNumber, int theMinLength = 2 );
  static QString ColorToHex( const QColor& theColor );
};
