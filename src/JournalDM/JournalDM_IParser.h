
#pragma once

#include <JournalDM.h>
#include <JournalDM_Exercise.h>
#include <QString>
#include <QList>

class JOURNAL_DM_API JournalDM_IParser
{
public:
  virtual JournalDM_ExerciseList extractData( const QString& theLine,
                                              bool& isBlockNext ) const = 0;
};
