
#include <JournalGUI_SimpleInputCard.h>
#include <JournalGUI_LineEdit.h>
#include <JournalGUI_QuestionLabel.h>
#include <QApplication>
#include <QGridLayout>
#include <QLineEdit>
#include <QPushButton>

JournalGUI_SimpleInputCard::JournalGUI_SimpleInputCard( QWidget* theParent )
  : JournalGUI_ExerciseCard( theParent )
{
  QGridLayout* aLayout = layout();

  myQuestion = new JournalGUI_QuestionLabel( this );
  myQuestion->setAlignment( Qt::AlignCenter );
  myAnswer = new JournalGUI_LineEdit( this );

  aLayout->addWidget( myQuestion, 0, 0, 1, 2 );
  aLayout->addWidget( myAnswer, 1, 0, 1, 2 );

  connect( myAnswer, SIGNAL( returnPressed() ), this, SLOT( OnFinish() ) );
}

JournalGUI_SimpleInputCard::~JournalGUI_SimpleInputCard()
{
}

void JournalGUI_SimpleInputCard::SetExercise( const JournalDM_ExerciseData& theData )
{
  JournalGUI_ExerciseCard::SetExercise( theData );
  myQuestion->setText( theData.Question );
  myAnswer->setText( "" );
  myAnswer->setFocus();
  myCorrectAnswer = theData.Answer;
}

QString JournalGUI_SimpleInputCard::GetAnswer() const
{
  return myAnswer->text();
}
