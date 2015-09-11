
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
  MapOfResults::iterator anIt = myResults.find( aKey );
  if( anIt==myResults.end() )
  {
    Result aResult;
    aResult.Average = theResult;
    aResult.Nb = 1;
    myResults.insert( aKey, aResult );
  }
  else
  {
    Result& aResult = anIt.value();
    double& a = aResult.Average;
    int& n = aResult.Nb;
    a = ( a * n + theResult ) / ( n + 1 );
    n++;
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
