
#pragma once

#include <QGraphicsView>
#include <JournalDM_Exercise.h>

class QGridLayout;
class QFrame;

class JournalGUI_ExerciseCard : public QGraphicsView
{
public:
  JournalGUI_ExerciseCard( QWidget* theParent = 0 );
  ~JournalGUI_ExerciseCard();

  virtual void SetExercise( const JournalDM_ExerciseData& );
  JournalDM_ExerciseData GetExercise() const;

protected:
  void resizeEvent( QResizeEvent* theEvent ) override;

  QGridLayout* layout() const;

private:
  QPixmap                myShadow;
  double                 myShrink;
  double                 myDelta;
  JournalDM_ExerciseData myExercise;

  QGraphicsPixmapItem*   myPixmapItem;
  QGraphicsProxyWidget*  myFrameItem;
};
