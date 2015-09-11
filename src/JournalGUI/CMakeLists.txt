
include(../../cmake/common.cmake)

set( PROJECT_HEADERS 
  JournalGUI_ExerciseCard.h
  JournalGUI_LineEdit.h
  JournalGUI_SimpleInputCard.h
)

set( PROJECT_MOC_HEADERS
  JournalGUI_ExerciseCard.h
  JournalGUI_LineEdit.h
  JournalGUI_SimpleInputCard.h
)

set( PROJECT_SOURCES
  JournalGUI.cpp
  JournalGUI_ExerciseCard.cpp
  JournalGUI_LineEdit.cpp
  JournalGUI_SimpleInputCard.cpp
)

include(../../cmake/qt.cmake)

include_directories( ../JournalDM )
set( PROJECT_LIBRARIES JournalDM )

add_definitions( -D_CRT_SECURE_NO_WARNINGS )
add_executable( JournalGUI ${PROJECT_SOURCES} ${PROJECT_MOCS} ${PROJECT_HEADERS} )
target_link_libraries( JournalGUI ${PROJECT_LIBRARIES} ${QT_CORE} ${QT_GUI} )
