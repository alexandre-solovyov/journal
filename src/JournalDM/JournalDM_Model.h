
#pragma once

#include <JournalDM.h>
#include <QObject>
#include <QList>

class JournalDM_Category;
struct JournalDM_ExerciseData;
class JournalDM_IParser;

class JOURNAL_DM_API JournalDM_Model : public QObject
{
public:
  JournalDM_Model();
  ~JournalDM_Model();

  bool Load( const QString& thePath );

  int GetNbCategories() const;
  JournalDM_Category* GetCategory( int theIndex ) const;

  JournalDM_ExerciseData GetRandomExercise() const;

protected:
  bool LoadFile( const QString& thePath );
  bool LoadFolder( const QString& thePath );
  void InitParsers();

private:
  QList<JournalDM_Category*> myCategories;
  QList<JournalDM_IParser*>  myParsers;
};
