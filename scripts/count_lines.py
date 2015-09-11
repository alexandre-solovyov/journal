
import os

def count_in_file( theFile ):
  aLines = open( theFile, 'r' ).readlines()
  return len( aLines )

def count_in_list( theFolder, theList ):
  aCount = 0
  for aFile in theList:
    aPath = theFolder + '/' + aFile
    aLocal = count_in_file( aPath )
    print aPath, aLocal
    aCount = aCount + aLocal
  return aCount

def count_in_folder( theFolder ):
  aCount = 0
  aFiles = os.listdir( theFolder )
  aHeaders    = filter( lambda x: x.endswith('.h'),   aFiles )
  aSourcesCpp = filter( lambda x: x.endswith('.cpp'), aFiles )
  aCount = aCount + count_in_list( theFolder, aHeaders )
  aCount = aCount + count_in_list( theFolder, aSourcesCpp )
  return aCount
    
def count_in_folders( theRoot, theFoldersList ):
  aCount = 0
  for aFolder in theFoldersList:
    aCount = aCount + count_in_folder( theRoot + '/' + aFolder )
  return aCount

aFoldersList = [ 'JournalConsole', 'JournalDM', 'JournalDM_tests', 'JournalGUI', 'TestLib' ]

print count_in_folders( '../src', aFoldersList )
