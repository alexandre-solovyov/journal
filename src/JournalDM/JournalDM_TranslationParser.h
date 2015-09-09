
#pragma once

#include <JournalDM_IParser.h>
#include <QObject>

class JournalDM_Model;

class JOURNAL_DM_API JournalDM_TranslationParser : public JournalDM_IParser,
                                                   public QObject
{
public:
  JournalDM_TranslationParser( JournalDM_Model* );
  virtual ~JournalDM_TranslationParser();

  JournalDM_ExerciseList extractData( const QString& theLine,
                                      bool& isBlockNext ) const override;
};
