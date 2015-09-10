
#include <JournalGUI_Window.h>
#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QResizeEvent>
#include <QGraphicsBlurEffect>

JournalGUI_Window::JournalGUI_Window( QWidget* theParent )
  : QWidget( theParent )
{
  myRotationDeg = -3;
  myShrink = 0.8;
  myDelta = 30;

  setWindowFlags( Qt::Window | Qt::FramelessWindowHint );
  setAttribute( Qt::WA_TranslucentBackground );
}

JournalGUI_Window::~JournalGUI_Window()
{
}

QImage applyEffectToImage( QPixmap theSource, QGraphicsEffect* theEffect )
{
  QGraphicsScene aScene;
  QGraphicsPixmapItem anItem;
  anItem.setPixmap( theSource );
  anItem.setGraphicsEffect( theEffect );
  aScene.addItem( &anItem );
  QImage aResult( theSource.size(), QImage::Format_ARGB32 );
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

void JournalGUI_Window::resizeEvent( QResizeEvent* theEvent )
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
  myShadow = QPixmap::fromImage( applyEffectToImage( aShadow, aBlur ) );
}

void JournalGUI_Window::paintEvent( QPaintEvent* theEvent )
{
  QWidget::paintEvent( theEvent );

  QPainter aPainter( this );
  aPainter.setRenderHint( QPainter::Antialiasing );
  aPainter.setRenderHint( QPainter::TextAntialiasing );
  aPainter.setRenderHint( QPainter::SmoothPixmapTransform	);
  aPainter.setRenderHint( QPainter::HighQualityAntialiasing );

  QRect r = rect();
  QRectF rs = shrink( r, myShrink );

  int w = r.width();
  int h = r.height();
  int d = -10;

  //aPainter.fillRect( r, Qt::blue );

  aPainter.save();

  aPainter.translate( w/2, h/2 );
  aPainter.rotate( myRotationDeg );
  aPainter.translate( -w/2, -h/2 );

  aPainter.drawPixmap( r, myShadow, r );
  aPainter.fillRect( moveR( rs, d, d ), Qt::white );

  aPainter.restore();
}
