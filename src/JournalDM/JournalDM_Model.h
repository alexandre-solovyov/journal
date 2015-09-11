
#pragma once

#include <JournalDM_Exercise.h>
#include <QObject>
#include <QList>

class JournalDM_Category;
;
class JournalDM_IParser;

class JOURNAL_DM_API JournalDM_Model : public QObject
{
public:
  JournalDM_Model();
  ~JournalDM_Model();

  bool Load( const QString& thePath );

  int GetNbCategories() const;
  JournalDM_Category* GetCategory( int theIndex ) const;

  JournalDM_ExerciseList GetRandomExercises( int theNbExercises ) const;

protected:
  bool LoadFile( const QString& thePath );
  bool LoadFolder( const QString& thePath );
  void InitParsers();

private:
  QList<JournalDM_Category*> myCategories;
  QList<JournalDM_IParser*>  myParsers;
};
