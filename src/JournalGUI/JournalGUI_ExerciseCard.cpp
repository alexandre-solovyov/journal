
#include <JournalGUI_ExerciseCard.h>
#include <JournalDM_Tools.h>
#include <QFrame>
#include <QGraphicsBlurEffect>
#include <QGraphicsProxyWidget>
#include <QGraphicsScene>
#include <QGridLayout>
#include <QLabel>
#include <QPainter>
#include <QPushButton>
#include <QResizeEvent>

const int MAX_NB_ROWS = 100;

JournalGUI_ExerciseCard::JournalGUI_ExerciseCard( QWidget* theParent )
  : QGraphicsView( theParent )
{
  myShrink = 0.8;
  myDelta = -10;
  myShadowColor = QColor( 64, 64, 64, 200 );
  myBlurRadius = 20;
  myIsFinished = false;

  QGraphicsScene* aScene = new QGraphicsScene( this );
  setScene( aScene );
  
  setWindowFlags( Qt::Window | Qt::FramelessWindowHint );
  setAttribute( Qt::WA_TranslucentBackground );
  setFrameShape( QFrame::NoFrame );

  myShadowItem = new QGraphicsRectItem();
  myShadowItem->setBrush( myShadowColor );
  QGraphicsBlurEffect* aBlur = new QGraphicsBlurEffect( this );
  aBlur->setBlurRadius( myBlurRadius );
  myShadowItem->setGraphicsEffect( aBlur );
  aScene->addItem( myShadowItem );

  QFrame* aMainFrame = new QFrame( 0 );
  QVBoxLayout* aLayout = new QVBoxLayout( aMainFrame );

  QGridLayout* aMainLayout = new QGridLayout( 0 );
  QHBoxLayout* aStatusLayout = new QHBoxLayout( 0 );
  aLayout->addLayout( aMainLayout, 1 );
  aLayout->addLayout( aStatusLayout, 0 );

  myStateLabel = new QLabel( "", this );
  aStatusLayout->addWidget( myStateLabel, 1 );

  myVerify = new QPushButton( tr( "Verify" ), this );
  connect( myVerify, SIGNAL( clicked() ), this, SLOT( OnFinish() ) );
  aStatusLayout->addWidget( myVerify, 0 );

  myNext = new QPushButton( tr( "Next" ), this );
  connect( myNext, SIGNAL( clicked() ), this, SIGNAL( next() ) );
  aStatusLayout->addWidget( myNext, 0 );
  
  aMainLayout->setColumnStretch( 0, 1 );
  aMainLayout->setRowStretch( MAX_NB_ROWS, 1 );

  myFrameItem = aScene->addWidget( aMainFrame );
}

JournalGUI_ExerciseCard::~JournalGUI_ExerciseCard()
{
}

void JournalGUI_ExerciseCard::SetExercises( const JournalDM_ExerciseList& theList )
{
  myExercises = theList;
  SetReadOnly( false );
}

JournalDM_ExerciseList JournalGUI_ExerciseCard::GetExercises() const
{
  return myExercises;
}

QRectF shrink( const QRect& theRect, double theShrink )
{
  QPointF c = theRect.center();
  QPointF tl = theRect.topLeft();
  QPointF tls = c + ( tl-c ) * theShrink;
  QSizeF s = theRect.size();
  s *= theShrink;
  return QRectF( tls, s );
}

QRectF moveR( const QRectF& theRect, int theDx, int theDy )
{
  QPointF tl = theRect.topLeft() + QPointF( theDx, theDy );
  return QRectF( tl, theRect.size() );
}

void JournalGUI_ExerciseCard::resizeEvent( QResizeEvent* theEvent )
{
  QWidget::resizeEvent( theEvent );

  QRect r( QPoint(), theEvent->size() );
  QRectF rs = shrink( r, myShrink );
  myShadowItem->setRect( rs );
  
  QRectF aCardRect = moveR( rs, myDelta, myDelta );
  myFrameItem->setGeometry( aCardRect );
}

QGridLayout* JournalGUI_ExerciseCard::GetLayout() const
{
  return dynamic_cast<QGridLayout*>( myFrameItem->widget()->layout()->itemAt( 0 )->layout() );
}

void JournalGUI_ExerciseCard::OnFinish()
{
  if( myIsFinished )
    return;

  QString aStatus;
  QColor aStatusColor;
  SetReadOnly( true );
  double aResult = Verify( aStatus, aStatusColor );
  emit finish( aResult );

  myStateLabel->setText( aStatus );
  QString aStyleSheet = "color: #" + JournalDM_Tools::ColorToHex( aStatusColor );
  myStateLabel->setStyleSheet( aStyleSheet );
}

void JournalGUI_ExerciseCard::SetReadOnly( bool isReadOnly )
{
  myVerify->setVisible( !isReadOnly );
  myNext->setVisible( isReadOnly );
  if( !isReadOnly )
    myStateLabel->setText( "" );
  myIsFinished = isReadOnly;
}

void JournalGUI_ExerciseCard::keyPressEvent( QKeyEvent* theEvent )
{
  if( myIsFinished && 
      ( theEvent->key()==Qt::Key_Return || theEvent->key()==Qt::Key_Enter ) )
  {
    emit next();
    theEvent->accept();
    return;
  }

  QGraphicsView::keyPressEvent( theEvent );
}
