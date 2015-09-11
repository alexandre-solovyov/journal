
#pragma once

#include <QObject>

class JournalDM_Model;
class JournalGUI_ExerciseCard;

class JournalGUI_ExerciseManager : public QObject
{
  Q_OBJECT

public:
  JournalGUI_ExerciseManager( JournalDM_Model* theModel );
  ~JournalGUI_ExerciseManager();

  void RandomExerciseOn( JournalGUI_ExerciseCard* );

protected slots:
  void OnFinish( double );
  void OnNext();

private:
  JournalDM_Model* myModel;
};
