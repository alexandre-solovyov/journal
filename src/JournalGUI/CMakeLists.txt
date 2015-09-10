
include(../../cmake/common.cmake)
include(../../cmake/qt.cmake)

set( PROJECT_HEADERS 
  JournalGUI_Window.h
)

set( PROJECT_SOURCES
  JournalGUI.cpp
  JournalGUI_Window.cpp
)

add_definitions( -D_CRT_SECURE_NO_WARNINGS )
add_executable( JournalGUI ${PROJECT_SOURCES} ${PROJECT_HEADERS} )
target_link_libraries( JournalGUI ${PROJECT_LIBRARIES} ${QT_CORE} ${QT_GUI} )
