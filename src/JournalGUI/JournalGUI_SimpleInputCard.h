
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

  void SetExercises( const JournalDM_ExerciseList& ) override;
  int GetNbData() const override;
  QSize sizeHint() const override;

protected:
  double Verify( QString&, QColor& ) override;
  void SetReadOnly( bool ) override;

private:
  QLabel*       myQuestion;
  QLineEdit*    myAnswer;
  QString       myCorrectAnswer;
};
