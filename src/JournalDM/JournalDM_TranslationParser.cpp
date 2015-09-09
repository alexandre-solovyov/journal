
#include <JournalDM_TranslationParser.h>
#include <JournalDM_Constants.h>
#include <JournalDM_Model.h>

JournalDM_TranslationParser::JournalDM_TranslationParser( JournalDM_Model* theModel )
  : QObject( theModel )
{
}

JournalDM_TranslationParser::~JournalDM_TranslationParser()
{
}

JournalDM_ExerciseList JournalDM_TranslationParser::extractData( const QString& theLine,
                                                                 bool& isBlockNext ) const
{
  isBlockNext = true;
  JournalDM_ExerciseList aResult;
  aResult.reserve( LIST_RESERVE );

  int anIndex = theLine.indexOf( TRANSLATION_MARK );
  if( anIndex < 0 )
    return aResult;

  QString aPartLeft = theLine.left( anIndex ).trimmed();
  int aStart = anIndex+TRANSLATION_MARK.length();
  QString aPartRight = theLine.mid( aStart, theLine.size()-aStart+1 ).trimmed();
  QString aQuestionPattern = QString( "%0" ) + TRANSLATION_MARK + "%1";
  aResult.append( aQuestionPattern.arg( PLACEHOLDER ).arg( aPartRight ), aPartLeft );
  aResult.append( aQuestionPattern.arg( aPartLeft ).arg( PLACEHOLDER ), aPartRight );

  return aResult;
}
