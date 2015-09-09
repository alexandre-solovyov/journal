
#include <JournalDM_Model.h>
#include <JournalDM_Category.h>
#include <JournalDM_StdParser.h>
#include <QDir>
#include <QFileInfo>

JournalDM_Model::JournalDM_Model()
{
}

JournalDM_Model::~JournalDM_Model()
{
}

void JournalDM_Model::InitParsers()
{
  myParsers.append( new JournalDM_StdParser( this ) );
}

bool JournalDM_Model::Load( const QString& thePath )
{
  QFileInfo anInfo( thePath );
  if( anInfo.isDir() )
    return LoadFolder( thePath );
  else
    return LoadFile( thePath );
}

bool JournalDM_Model::LoadFolder( const QString& thePath )
{
  QDir aFolder( thePath );
  QStringList	aFilesList = aFolder.entryList();
  bool isOK = true;
  foreach( QString aFile, aFilesList )
  {
    bool isFileOK = LoadFile( aFile );
    isOK = isOK && isFileOK;
  }
  return isOK;
}

bool JournalDM_Model::LoadFile( const QString& thePath )
{
  if( myParsers.empty() )
    InitParsers();

  QString aName = QFileInfo( thePath ).baseName();
  JournalDM_Category* aCategory = new JournalDM_Category( this, aName );
  if( !aCategory->Load( thePath, myParsers ) )
  {
    aCategory->deleteLater();
    return false;
  }

  myCategories.append( aCategory );
  return true;
}

int JournalDM_Model::GetNbCategories() const
{
  return myCategories.size();
}

JournalDM_Category* JournalDM_Model::GetCategory( int theIndex ) const
{
  if( theIndex>=0 && theIndex<GetNbCategories() )
    return myCategories[theIndex];
  else
    return 0;
}
