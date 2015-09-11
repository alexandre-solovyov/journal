
#include <JournalGUI_SimpleInputCard.h>
#include <JournalGUI_LineEdit.h>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

JournalGUI_SimpleInputCard::JournalGUI_SimpleInputCard( QWidget* theParent )
  : JournalGUI_ExerciseCard( theParent )
{
  QFont aQuestionFont( "Georgia", 16 );
  aQuestionFont.setBold( false );
  QFont anAnswerFont = aQuestionFont;
  aQuestionFont.setBold( true );

  QGridLayout* aLayout = layout();

  myQuestion = new QLabel( "QUESTION", this );
  myQuestion->setFont( aQuestionFont );
  myAnswer = new JournalGUI_LineEdit( this );
  myAnswer->setFont( anAnswerFont );
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
  myQuestion->setText( theData.Question );
  myAnswer->setText( "" );
  myCorrectAnswer = theData.Answer;
}
