
#include <JournalDM_StdParser.h>
#include <JournalDM_Constants.h>
#include <JournalDM_Model.h>
#include <JournalDM_Tools.h>

JournalDM_StdParser::JournalDM_StdParser( JournalDM_Model* theModel )
  : QObject( theModel )
{
}

JournalDM_StdParser::~JournalDM_StdParser()
{
}

JournalDM_ExerciseList JournalDM_StdParser::extractData( const QString& theLine,
                                                         bool& isBlockNext ) const
{
  isBlockNext = false;
  JournalDM_ExerciseList aResult;
  JournalDM_ExerciseData aData;
  aResult.reserve( LIST_RESERVE );

  int aNbMarkedParts = 0;
  for( int i=0, n=theLine.size(); i<n; i++ )
  {
    if( theLine[i] != WORD_MARK )
      continue;

    int aStart = i+1;
    int j = i+1;
    while( j<n && theLine[j].isLetter() )
      j++;
    int aLen = j-i-1;

    aData.Answer = theLine.mid( aStart, aLen );
    aData.Question = theLine;
    aData.Question.replace( aStart-1, aLen+1, PLACEHOLDER );
    aData.Question.remove( WORD_MARK );

    aResult.append( aData );
    aNbMarkedParts++;
  }

  if( aNbMarkedParts==0 )
  {
    // all words are considered as marked
    QStringList aWords = theLine.split( ' ', QString::SkipEmptyParts );
    for( int i=0, n=aWords.size(); i<n; i++ )
      if( JournalDM_Tools::IsWord( aWords[i] ) )
      {
        aData.Answer = aWords[i];
        aWords[i] = PLACEHOLDER;
        aData.Question = aWords.join( " " );
        aWords[i] = aData.Answer;
        aResult.append( aData );
      }
  }

  return aResult;
}
