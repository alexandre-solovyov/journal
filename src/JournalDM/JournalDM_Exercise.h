
#pragma once

#include <QString>
#include <QList>

struct JournalDM_ExerciseData
{
  QString Question;
  QString Answer;
};

class JournalDM_ExerciseList : public QList<JournalDM_ExerciseData>
{
public:
  using QList<JournalDM_ExerciseData>::append;
  void append( const QString& theQuestion, const QString& theAnswer );
};
