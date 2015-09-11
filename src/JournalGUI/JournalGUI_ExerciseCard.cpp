
#include <JournalGUI_ExerciseCard.h>
#include <QApplication>
#include <QPainter>
#include <QGraphicsScene>
#include <QResizeEvent>
#include <QGraphicsBlurEffect>
#include <QGraphicsProxyWidget>
#include <QGridLayout>
#include <QFrame>
#include <QMessageBox>

JournalGUI_ExerciseCard::JournalGUI_ExerciseCard( QWidget* theParent )
  : QGraphicsView( theParent )
{
  myShrink = 0.8;
  myDelta = -10;
  myShadowColor = QColor( 64, 64, 64, 200 );
  myBlurRadius = 20;

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

  QFrame* aFrame = new QFrame( 0 );
  aFrame->setLayout( new QGridLayout( aFrame ) );
  myFrameItem = aScene->addWidget( aFrame );
}

JournalGUI_ExerciseCard::~JournalGUI_ExerciseCard()
{
}

void JournalGUI_ExerciseCard::SetExercise( const JournalDM_ExerciseData& theExercise )
{
  myExercise = theExercise;
}

JournalDM_ExerciseData JournalGUI_ExerciseCard::GetExercise() const
{
  return myExercise;
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

QGridLayout* JournalGUI_ExerciseCard::layout() const
{
  return dynamic_cast<QGridLayout*>( myFrameItem->widget()->layout() );
}

void JournalGUI_ExerciseCard::OnFinish()
{
  QMessageBox::information( qApp->topLevelWidgets().first(), "Info", "Finish" );
}
