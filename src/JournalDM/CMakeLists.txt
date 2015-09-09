
include(../../cmake/common.cmake)
include(../../cmake/qt.cmake)

set( PROJECT_HEADERS 
  JournalDM.h
  JournalDM_Category.h
  JournalDM_Constants.h
  JournalDM_Exercise.h
  JournalDM_IParser.h
  JournalDM_Model.h
  JournalDM_StdParser.h
  JournalDM_Tools.h
  JournalDM_TranslationParser.h
)

set( PROJECT_SOURCES
  JournalDM_Category.cpp
  JournalDM_Exercise.cpp
  JournalDM_Model.cpp
  JournalDM_StdParser.cpp
  JournalDM_Tools.cpp
  JournalDM_TranslationParser.cpp
)

add_definitions( -DJOURNAL_DM_EXPORTS -D_CRT_SECURE_NO_WARNINGS )
add_library( JournalDM SHARED ${PROJECT_SOURCES} ${PROJECT_HEADERS} )
set_target_properties( JournalDM PROPERTIES LINK_INTERFACE_LIBRARIES "" )
target_link_libraries( JournalDM ${PROJECT_LIBRARIES} ${CPPUNIT_LIBRARIES} ${QT_CORE} )

install_files( /include FILES ${PROJECT_HEADERS} )
