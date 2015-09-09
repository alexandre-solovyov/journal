
#include <JournalDM_Exercise.h>

void JournalDM_ExerciseList::append( const QString& theQuestion, const QString& theAnswer )
{
  JournalDM_ExerciseData aData;
  aData.Question = theQuestion;
  aData.Answer = theAnswer;
  append( aData );
}
