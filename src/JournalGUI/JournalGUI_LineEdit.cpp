
#include <JournalGUI_LineEdit.h>
#include <QKeyEvent>

JournalGUI_LineEdit::JournalGUI_LineEdit( QWidget* theParent )
: QLineEdit( theParent )
{
}

JournalGUI_LineEdit::~JournalGUI_LineEdit()
{
}

void JournalGUI_LineEdit::keyPressEvent( QKeyEvent* e )
{
  int aPos = cursorPosition();
  QString aText = text();
  if( aPos>0 && aPos<=aText.length() )
  {
    QChar aPrev = aText[aPos-1];
    QString anEText = e->text();
    QChar aModifier = anEText.length() > 0 ? anEText[0] : QChar(0);
    QString aTrans = transform( aPrev, aModifier );
    if( !aTrans.isEmpty() )
    {
      aText[aPos-1] = aTrans[0];
      int aStart = selectionStart(), aLen = selectedText().length();
      setText( aText );
      if( aStart >= 0 && aLen > 0 )
      {
        if( aPos==aStart )
        {
          aStart += aLen;
          aLen = -aLen;
        }
        setSelection( aStart, aLen );
      }
      e->accept();
      return;
    }
  }
  QLineEdit::keyPressEvent( e );
}

QString CHARS = "aceiouysnACEIOUYSN";
QString MODIFIERS = "\\/^:+";
QChar STD_TRANSFORM[18][5] = 
{
  //  \       /       ^       :       +
  { 0x00E0, 0x00E1, 0x00E2, 0x00E4, 0x00E6 }, // a
  { 0x0000, 0x0000, 0x0000, 0x0000, 0x00E7 }, // c
  { 0x00E8, 0x00E9, 0x00EA, 0x00EB, 0x0000 }, // e
  { 0x00EC, 0x00ED, 0x00EE, 0x00EF, 0x0000 }, // i
  { 0x00F2, 0x00F3, 0x00F4, 0x00F6, 0x0153 }, // o
  { 0x00F9, 0x00FA, 0x00FB, 0x00FC, 0x0000 }, // u
  { 0x0000, 0x00FD, 0x0000, 0x0000, 0x0000 }, // y
  { 0x0000, 0x0000, 0x0000, 0x0000, 0x00DF }, // s
  { 0x0000, 0x0000, 0x0000, 0x0000, 0x00F1 }, // n

  { 0x00C0, 0x00C1, 0x00C2, 0x00C4, 0x00C6 }, // A
  { 0x0000, 0x0000, 0x0000, 0x0000, 0x00C7 }, // C
  { 0x00C8, 0x00C9, 0x00CA, 0x00CB, 0x0000 }, // E
  { 0x00CC, 0x00CD, 0x00CE, 0x00CF, 0x0000 }, // I
  { 0x00D2, 0x00D3, 0x00D4, 0x00D6, 0x0152 }, // O
  { 0x00D9, 0x00DA, 0x00DB, 0x00DC, 0x0000 }, // U
  { 0x0000, 0x00DD, 0x0000, 0x0000, 0x0000 }, // Y
  { 0x0000, 0x0000, 0x0000, 0x0000, 0x0000 }, // S
  { 0x0000, 0x0000, 0x0000, 0x0000, 0x00D1 }  // N
};

QString JournalGUI_LineEdit::transform( const QChar& theChar, const QChar& theModifier )
{
  int aCharInd = CHARS.indexOf( theChar );
  int aModInd = MODIFIERS.indexOf( theModifier );
  if( aCharInd<0 || aModInd<0 )
    return "";
  else
  {
    QChar aTr = STD_TRANSFORM[aCharInd][aModInd];
    if( aTr==0 )
      return "";
    else
      return aTr;
  }
}
