
#pragma once

#include <JournalGUI_ExerciseCard.h>

class QLabel;
class QLineEdit;

class JournalGUI_SimpleInputCard : public JournalGUI_ExerciseCard
{
  Q_OBJECT

public:
  JournalGUI_SimpleInputCard( QWidget* theParent = 0 );
  virtual ~JournalGUI_SimpleInputCard();

  void SetExercise( const JournalDM_ExerciseData& ) override;

protected:
  QString GetAnswer() const override;

private:
  QLabel*       myQuestion;
  QLineEdit*    myAnswer;
  QString       myCorrectAnswer;
};
