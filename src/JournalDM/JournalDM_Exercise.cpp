
#include <JournalDM_Exercise.h>
#include <QHash>

uint JournalDM_ExerciseData::GetHash() const
{
  return qHash( Question + Answer );
}

void JournalDM_ExerciseList::append( const QString& theQuestion, const QString& theAnswer )
{
  JournalDM_ExerciseData aData;
  aData.Question = theQuestion;
  aData.Answer = theAnswer;
  append( aData );
}
