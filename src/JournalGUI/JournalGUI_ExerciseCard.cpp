
#include <JournalGUI_ExerciseCard.h>
#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QResizeEvent>
#include <QGraphicsBlurEffect>
#include <QGraphicsProxyWidget>
#include <QGridLayout>
#include <QFrame>

JournalGUI_ExerciseCard::JournalGUI_ExerciseCard( QWidget* theParent )
  : QGraphicsView( theParent )
{
  myShrink = 0.8;
  myDelta = -10;

  QGraphicsScene* aScene = new QGraphicsScene( this );
  setScene( aScene );
  
  setWindowFlags( Qt::Window | Qt::FramelessWindowHint );
  setAttribute( Qt::WA_TranslucentBackground );
  setStyleSheet( "background: transparent" );
  setFrameShape( QFrame::NoFrame );

  myPixmapItem = new QGraphicsPixmapItem();
  aScene->addItem( myPixmapItem );

  QFrame* aFrame = new QFrame( 0 );
  myFrameItem = aScene->addWidget( aFrame );
  new QGridLayout( aFrame );
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

QPixmap applyEffectToImage( const QPixmap& theSource, QGraphicsEffect* theEffect )
{
  QGraphicsScene aScene;
  QGraphicsPixmapItem anItem;
  anItem.setPixmap( theSource );
  anItem.setGraphicsEffect( theEffect );
  aScene.addItem( &anItem );
  QPixmap aResult( theSource.width(), theSource.height() );
  aResult.fill( Qt::transparent );
  QPainter aPainter( &aResult );
  aScene.render( &aPainter, QRectF(), QRectF( 0, 0, theSource.width(), theSource.height() ) );
  return aResult;
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

  // Create a shadow image
  QRect r( QPoint(), theEvent->size() );
  QRectF rs = shrink( r, myShrink );

  QPixmap aShadow = QPixmap( r.size() );
  aShadow.fill( Qt::transparent );
  QPainter aPainter( &aShadow );

  int aGray = 64;
  int aGrayTr = 200;
  aPainter.fillRect( rs, QColor( aGray, aGray, aGray, aGrayTr ) );

  QGraphicsBlurEffect* aBlur = new QGraphicsBlurEffect();
  aBlur->setBlurRadius( 20 );
  myShadow = applyEffectToImage( aShadow, aBlur );

  myPixmapItem->setPixmap( myShadow );
  myPixmapItem->setPos( 0, 0 );
  
  QRectF aCardRect = moveR( rs, myDelta, myDelta );
  myFrameItem->setGeometry( aCardRect );
}

QGridLayout* JournalGUI_ExerciseCard::layout() const
{
  return dynamic_cast<QGridLayout*>( myFrameItem->widget()->layout() );
}
