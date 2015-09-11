
#pragma once

#include <QGraphicsView>
#include <JournalDM_Exercise.h>

class QGridLayout;
class QLabel;
class QPushButton;

class JournalGUI_ExerciseCard : public QGraphicsView
{
  Q_OBJECT

public:
  JournalGUI_ExerciseCard( QWidget* theParent = 0 );
  virtual ~JournalGUI_ExerciseCard();

  virtual void SetExercises( const JournalDM_ExerciseList& );
  JournalDM_ExerciseList GetExercises() const;

  virtual int GetNbData() const = 0;
  
protected:
  void resizeEvent( QResizeEvent* theEvent ) override;
  void keyPressEvent( QKeyEvent* theEvent ) override;

  QGridLayout* GetLayout() const;

  virtual double Verify( QString&, QColor& ) = 0;
  virtual void SetReadOnly( bool );

signals:
  void finish( double );
  void next();

protected slots:
  void OnFinish();

private:
  double                 myShrink;
  double                 myDelta;
  QColor                 myShadowColor;
  int                    myBlurRadius;
  JournalDM_ExerciseList myExercises;

  QGraphicsRectItem*     myShadowItem;
  QGraphicsProxyWidget*  myFrameItem;
  QLabel*                myStateLabel;

  QPushButton*           myVerify;
  QPushButton*           myNext;
  bool                   myIsFinished;
};
