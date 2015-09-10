
#include <JournalGUI_SimpleInputCard.h>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

JournalGUI_SimpleInputCard::JournalGUI_SimpleInputCard( QWidget* theParent )
  : JournalGUI_ExerciseCard( theParent )
{
  QFont aFont( "Arial", 14 );
  aFont.setBold( true );

  QGridLayout* aLayout = layout();

  myQuestion = new QLabel( "QUESTION", this );
  myQuestion->setFont( aFont );
  myAnswer = new QLineEdit( this );
  myAnswer->setFont( aFont );
  myReady = new QPushButton( tr( "VERIFY" ), this );
  myReady->setFont( aFont );

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
