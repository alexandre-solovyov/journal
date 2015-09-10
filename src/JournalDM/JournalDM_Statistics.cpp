
#include <JournalDM_Statistics.h>
#include <JournalDM_Constants.h>
#include <JournalDM_Exercise.h>

JournalDM_Statistics::JournalDM_Statistics()
{
}

JournalDM_Statistics::~JournalDM_Statistics()
{
}

bool JournalDM_Statistics::Register( const JournalDM_ExerciseData& theExercise, double theResult )
{
  uint aKey = theExercise.GetHash();
  QMap<uint, double>::iterator anIt = myResults.find( aKey );
  if( anIt==myResults.end() )
    myResults.insert( aKey, theResult );
  else
  {
    double& r = anIt.value();
    int nb = STAT_NB_ATTEMPTS_WEIGHT;
    r = ( r * nb + theResult ) / ( nb + 1 );
  }
  return true;
}

bool JournalDM_Statistics::Load( const QString& )
{
  ///< \todo
  return true;
}

bool JournalDM_Statistics::Save( const QString& )
{
  ///< \todo
  return true;
}
