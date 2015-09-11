
#pragma once

#include <JournalDM.h>
#include <QString>
#include <QList>

struct JournalDM_ExerciseData
{
  QString Question;
  QString Answer;

  uint GetHash() const;
  bool operator==( const JournalDM_ExerciseData& ) const;
};

#pragma warning( disable: 4661 )

class JOURNAL_DM_API JournalDM_ExerciseList : public QList<JournalDM_ExerciseData>
{
public:
  using QList<JournalDM_ExerciseData>::append;
  void append( const QString& theQuestion, const QString& theAnswer );
};

