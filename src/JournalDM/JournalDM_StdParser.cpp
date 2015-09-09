
#include <JournalDM_StdParser.h>
#include <JournalDM_Constants.h>
#include <JournalDM_Model.h>

JournalDM_StdParser::JournalDM_StdParser( JournalDM_Model* theModel )
  : QObject( theModel )
{
}

JournalDM_StdParser::~JournalDM_StdParser()
{
}

QList<JournalDM_ExerciseData> JournalDM_StdParser::extractData( const QString& theLine ) const
{
  QList<JournalDM_ExerciseData> aResult;
  aResult.reserve( LIST_RESERVE );

  for( int i=0, n=theLine.size(); i<n; i++ )
  {
    if( theLine[i] != QUESTION_MARK )
      continue;

    int aStart = i+1;
    int j = i+1;
    while( j<n && theLine[j].isLetter() )
      j++;
    int aLen = j-i-1;

    JournalDM_ExerciseData aData;
    aData.Answer = theLine.mid( aStart, aLen );
    aData.Question = theLine;
    aData.Question.replace( aStart-1, aLen+1, PLACEHOLDER );

    aResult.append( aData );
  }

  return aResult;
}
