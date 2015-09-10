
#include <JournalDM_Category.h>
#include <JournalDM_Constants.h>
#include <JournalDM_IParser.h>
#include <JournalDM_Model.h>
#include <JournalDM_Tools.h>
#include <QFile>
#include <QTextStream>

JournalDM_Category::JournalDM_Category( JournalDM_Model* theModel, const QString& theName )
  : QObject( theModel ), myName( theName ), myNbNonEmptyLines( 0 )
{
  myExercises.reserve( LIST_RESERVE );
}

JournalDM_Category::~JournalDM_Category()
{
}

QString JournalDM_Category::GetName() const
{
  return myName;
}

bool JournalDM_Category::Load( const QString& thePath, const QList<JournalDM_IParser*>& theParsers )
{
  QFile aFile( thePath );
  if( !aFile.open( QFile::ReadOnly | QFile::Text ) )
    return false;

  QTextStream aStream( &aFile );
  while( !aStream.atEnd() )
  {
    QString aLine = aStream.readLine();
    myLines.append( aLine );
    GenerateExercises( aLine, theParsers );
  }
  aFile.close();
  return true;
}

int JournalDM_Category::GetNbLines( bool isOnlyNonEmpty ) const
{
  return isOnlyNonEmpty ? myNbNonEmptyLines : myLines.size();
}

int JournalDM_Category::GetNbExercises() const
{
  return myExercises.size();
}

JournalDM_ExerciseData JournalDM_Category::GetExercise( int theIndex ) const
{
  if( theIndex>=0 && theIndex<GetNbExercises() )
    return myExercises[theIndex];
  else
    return JournalDM_ExerciseData();
}

bool JournalDM_Category::GenerateExercises( const QString& theLine,
                                            const QList<JournalDM_IParser*>& theParsers )
{
  QString aLine = JournalDM_Tools::RemoveComments( theLine ).trimmed();
  if( aLine.isEmpty() )
    return false;

  myNbNonEmptyLines++;
  bool isBlockNext = false;
  foreach( JournalDM_IParser* aParser, theParsers )
  {
    JournalDM_ExerciseList aDataList = aParser->extractData( aLine, isBlockNext );
    if( !aDataList.empty() )
    {
      foreach( JournalDM_ExerciseData aData, aDataList )
        myExercises.append( aData );
      if( isBlockNext )
        return true;
    }
  }

  return true;
}

JournalDM_ExerciseData JournalDM_Category::GetRandomExercise() const
{
  int anExerciseIndex = rand() % GetNbExercises();
  return GetExercise( anExerciseIndex );
}
