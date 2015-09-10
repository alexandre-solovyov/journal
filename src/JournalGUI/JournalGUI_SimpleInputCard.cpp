
#include <JournalGUI_SimpleInputCard.h>
#include <JournalGUI_LineEdit.h>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

JournalGUI_SimpleInputCard::JournalGUI_SimpleInputCard( QWidget* theParent )
  : JournalGUI_ExerciseCard( theParent )
{
  QFont aQuestionFont( "Arial", 16 );
  aQuestionFont.setBold( false );
  QFont anAnswerFont = aQuestionFont;
  aQuestionFont.setBold( true );

  QGridLayout* aLayout = layout();

  myQuestion = new QLabel( "QUESTION", this );
  myQuestion->setFont( aQuestionFont );
  myAnswer = new JournalGUI_LineEdit( this );
  myAnswer->setFont( anAnswerFont );
  myReady = new QPushButton( tr( "Verify" ), this );

  aLayout->addWidget( myQuestion, 0, 0 );
  aLayout->addWidget( myAnswer, 1, 0 );
  aLayout->addWidget( myReady, 2, 0 );
  aLayout->setRowStretch( 3, 1 );
}

JournalGUI_SimpleInputCard::~JournalGUI_SimpleInputCard()
{
}

void JournalGUI_SimpleInputCard::SetExercise( const JournalDM_ExerciseData& theData )
{
  myQuestion->setText( theData.Question );
  myAnswer->setText( theData.Answer );
}
