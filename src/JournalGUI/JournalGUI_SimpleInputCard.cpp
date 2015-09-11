
#include <JournalGUI_SimpleInputCard.h>
#include <JournalGUI_LineEdit.h>
#include <QApplication>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

JournalGUI_SimpleInputCard::JournalGUI_SimpleInputCard( QWidget* theParent )
  : JournalGUI_ExerciseCard( theParent )
{
  QGridLayout* aLayout = layout();

  myQuestion = new QLabel( "QUESTION", this );
  myAnswer = new JournalGUI_LineEdit( this );
  myReady = new QPushButton( tr( "Verify" ), this );

  aLayout->addWidget( myQuestion, 0, 0, 1, 2 );
  aLayout->addWidget( myAnswer, 1, 0, 1, 2 );
  aLayout->addWidget( myReady, 2, 1 );
  aLayout->setRowStretch( 3, 1 );
  aLayout->setColumnStretch( 0, 1 );
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
