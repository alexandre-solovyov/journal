
#pragma once

#include <QWidget>

class JournalGUI_Window : public QWidget
{
public:
  JournalGUI_Window( QWidget* theParent = 0 );
  ~JournalGUI_Window();

protected:
  void paintEvent( QPaintEvent* theEvent ) override;
  void resizeEvent( QResizeEvent* theEvent ) override;

private:
  QPixmap myShadow;
  double myRotationDeg;
  double myShrink;
  double myDelta;
};
