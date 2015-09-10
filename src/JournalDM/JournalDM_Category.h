
#pragma once

#include <JournalDM.h>
#include <JournalDM_Exercise.h>
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

  int GetNbLines( bool isOnlyNonEmpty = false ) const;
  int GetNbExercises() const;
  JournalDM_ExerciseData GetExercise( int theIndex ) const;
  JournalDM_ExerciseData GetRandomExercise() const;

protected:
  bool GenerateExercises( const QString& theLine, const QList<JournalDM_IParser*>& theParsers );

private:
  QString                myName;
  QStringList            myLines;
  int                    myNbNonEmptyLines;
  JournalDM_ExerciseList myExercises;
};
