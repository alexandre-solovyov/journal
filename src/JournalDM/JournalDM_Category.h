
#pragma once

#include <JournalDM.h>
#include <JournalDM_ExerciseData.h>
#include <QObject>
#include <QStringList>

class JournalDM_Model;
class JournalDM_IParser;

class JOURNAL_DM_API JournalDM_Category : public QObject
{
public:
  JournalDM_Category( JournalDM_Model*, const QString& theName );
  ~JournalDM_Category();

  QString GetName() const;
  bool Load( const QString& thePath, const QList<JournalDM_IParser*>& theParsers );

  int GetNbLines() const;
  int GetNbExercises() const;
  JournalDM_ExerciseData GetExercise( int theIndex ) const;

protected:
  bool GenerateExercises( const QString& theLine, const QList<JournalDM_IParser*>& theParsers );

private:
  QString                       myName;
  QStringList                   myLines;
  QList<JournalDM_ExerciseData> myExercises;
};
