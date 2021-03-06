
#pragma once

#include <JournalDM.h>
#include <QMap>

struct JournalDM_ExerciseData;

class JOURNAL_DM_API JournalDM_Statistics
{
public:
  JournalDM_Statistics();
  ~JournalDM_Statistics();

  bool Register( const JournalDM_ExerciseData&, double );
  bool Load( const QString& );
  bool Save( const QString& );

private:
  struct Result
  {
    double Average;
    int    Nb;
  };
  typedef QMap<uint, Result> MapOfResults;
  MapOfResults myResults;
};
