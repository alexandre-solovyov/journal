
/**
  @file
  \brief Declaration of import/export specifications for classes
*/

#pragma once

#ifdef WIN32
  #ifdef JOURNAL_DM_EXPORTS
    #define JOURNAL_DM_API __declspec(dllexport)
  #else
    #define JOURNAL_DM_API __declspec(dllimport)
  #endif
#else
  #define JOURNAL_DM_API
#endif


