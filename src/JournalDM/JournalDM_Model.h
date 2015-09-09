
/**
  @file
  \brief Declaration of import/export specifications for classes
*/

#pragma once

#include <JournalDM.h>
#include <QString>

class JOURNAL_DM_API JournalDM_Model
{
public:
  JournalDM_Model();
  ~JournalDM_Model();

  bool load( const QString& thePath );
};
