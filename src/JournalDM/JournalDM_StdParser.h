
#pragma once

#include <JournalDM_IParser.h>
#include <QObject>

class JournalDM_Model;

class JOURNAL_DM_API JournalDM_StdParser : public JournalDM_IParser,
                                           public QObject
{
public:
  JournalDM_StdParser( JournalDM_Model* );
  virtual ~JournalDM_StdParser();

  virtual QList<JournalDM_ExerciseData> extractData( const QString& theLine ) const;
};
