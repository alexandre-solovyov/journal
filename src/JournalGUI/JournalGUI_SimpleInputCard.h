
#pragma once

#include <JournalGUI_ExerciseCard.h>

class QLabel;
class QLineEdit;
class QPushButton;

class JournalGUI_SimpleInputCard : public JournalGUI_ExerciseCard
{
public:
  JournalGUI_SimpleInputCard( QWidget* theParent = 0 );
  ~JournalGUI_SimpleInputCard();

  void SetExercise( const JournalDM_ExerciseData& ) override;

private:
  QLabel*       myQuestion;
  QLineEdit*    myAnswer;
  QPushButton*  myReady;
  QString       myCorrectAnswer;
};
