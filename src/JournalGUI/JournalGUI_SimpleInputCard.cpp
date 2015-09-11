
#include <JournalGUI_SimpleInputCard.h>
#include <JournalGUI_LineEdit.h>
#include <JournalGUI_QuestionLabel.h>
#include <JournalDM_Tools.h>
#include <JournalDM_Constants.h>
#include <QGridLayout>

JournalGUI_SimpleInputCard::JournalGUI_SimpleInputCard( QWidget* theParent )
  : JournalGUI_ExerciseCard( theParent )
{
  QGridLayout* aLayout = GetLayout();

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

int JournalGUI_SimpleInputCard::GetNbData() const
{
  return 1;
}

void JournalGUI_SimpleInputCard::SetExercises( const JournalDM_ExerciseList& theList )
{
  JournalGUI_ExerciseCard::SetExercises( theList );
  myQuestion->setText( theList[0].Question );
  myAnswer->setText( "" );
  myAnswer->setFocus();
  myCorrectAnswer = theList[0].Answer;
}

QSize JournalGUI_SimpleInputCard::sizeHint() const
{
  return QSize( 480, 320 );
}

double JournalGUI_SimpleInputCard::Verify( QString& theStatus, QColor& theColor )
{
  QString anExpectedAnswer = GetExercises().first().Answer;
  QString anActualAnswer = myAnswer->text().trimmed();

  bool isOK = anExpectedAnswer==anActualAnswer;
  theStatus = isOK ? tr( "Correct" ) : tr( "Incorrect" );
  theColor = isOK ? Qt::darkGreen : Qt::red;

  QString aCorrection = "<font color=#%0>%1</font>";
  QString aColorStr = JournalDM_Tools::ColorToHex( theColor );
  QString aQuestion = myQuestion->text();
  QString aCorrectedQuestion = aQuestion.replace( PLACEHOLDER, aCorrection.arg( aColorStr ).arg( anExpectedAnswer ) );
  myQuestion->setText( aCorrectedQuestion );

  return isOK ? 1.0 : 0.0;
}

void JournalGUI_SimpleInputCard::SetReadOnly( bool isReadOnly )
{
  myAnswer->setReadOnly( isReadOnly );
  JournalGUI_ExerciseCard::SetReadOnly( isReadOnly );
}
