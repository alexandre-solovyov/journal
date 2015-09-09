
#pragma once

#include <JournalDM.h>
#include <JournalDM_ExerciseData.h>
#include <QString>
#include <QList>

class JOURNAL_DM_API JournalDM_IParser
{
public:
  virtual QList<JournalDM_ExerciseData> extractData( const QString& theLine ) const = 0;
};
