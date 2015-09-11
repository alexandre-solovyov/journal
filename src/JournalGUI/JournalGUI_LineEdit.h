
#pragma once

#include <QLineEdit>

class JournalGUI_LineEdit : public QLineEdit
{
  Q_OBJECT

public:
  JournalGUI_LineEdit( QWidget* = 0 );
  virtual ~JournalGUI_LineEdit();

protected:
  virtual void keyPressEvent( QKeyEvent* );

  static QString transform( const QChar& theChar, const QChar& theModifier );
};

