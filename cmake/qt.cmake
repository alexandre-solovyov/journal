
cmake_minimum_required ( VERSION 2.6 )
cmake_policy ( SET CMP0011 NEW )

find_package( Qt4 REQUIRED )

qt4_wrap_cpp( PROJECT_MOCS ${PROJECT_MOC_HEADERS} )
source_group( "Generated Files" FILES ${PROJECT_MOCS} )

include_directories( $ENV{QTDIR}/include )
include_directories( $ENV{QTDIR}/include/QtCore )
include_directories( $ENV{QTDIR}/include/QtGui )
include_directories( $ENV{QTDIR}/include/QtTest )

link_directories( $ENV{QTDIR}/lib )

IF( ${WIN32} )
  set( QT_CORE optimized QtCore4 debug QtCored4 )
  set( QT_GUI  optimized QtGui4  debug QtGuid4  )
  set( QT_TEST optimized QtTest4 debug QtTestd4 )
ELSE()
  set( QT_CORE QtCore )
  set( QT_GUI  QtGui  )
  set( QT_TEST QtTest )
ENDIF()

qt4_add_translation( PROJECT_QM_FILES ${PROJECT_TS_FILES} )
source_group( "Translation Files" FILES ${PROJECT_TS_FILES} )

qt4_add_resources( PROJECT_COMPILED_RC_FILES ${PROJECT_RC_FILES} )
source_group( "Resource Files" FILES ${PROJECT_RC_FILES} )
