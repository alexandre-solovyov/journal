
#include <JournalGUI_ExerciseManager.h>
#include <JournalDM_Model.h>
#include <JournalGUI_ExerciseCard.h>
#include <QApplication>
#include <time.h>

JournalGUI_ExerciseManager::JournalGUI_ExerciseManager( JournalDM_Model* theModel )
  : QObject( theModel ), myModel( theModel )
{
  srand( time( 0 ) );
}

JournalGUI_ExerciseManager::~JournalGUI_ExerciseManager()
{
}

void JournalGUI_ExerciseManager::RandomExerciseOn( JournalGUI_ExerciseCard* theCard )
{
  // 1. Connect necessary signals
  connect( theCard, SIGNAL( finish( double ) ), this, SLOT( OnFinish( double ) ) );
  connect( theCard, SIGNAL( next() ), this, SLOT( OnNext() ) );

  // 2. Get exercices
  int aNb = theCard->GetNbData();
  JournalDM_ExerciseList aList = myModel->GetRandomExercises( aNb );

  // 3. Resize the card according to hints and show
  QSize aSize = theCard->sizeHint();
  double phi = 1.61803398875;
  int h = aSize.height();
  int w = ( int )( h * phi ); //normalize to gold aspect ratio
  theCard->setFixedSize( w, h );
  theCard->show();
  qApp->processEvents();
  theCard->SetExercises( aList );
}

void JournalGUI_ExerciseManager::OnFinish( double )
{
  JournalGUI_ExerciseCard* aCard = dynamic_cast<JournalGUI_ExerciseCard*>( sender() );
  aCard->disconnect( SIGNAL( finish( double ) ) );

  ///> \todo write result to the statistics
}

void JournalGUI_ExerciseManager::OnNext()
{
  JournalGUI_ExerciseCard* aCard = dynamic_cast<JournalGUI_ExerciseCard*>( sender() );
  aCard->disconnect( SIGNAL( next() ) );

  RandomExerciseOn( aCard ); ///> \todo  some control on number of exercises
}
