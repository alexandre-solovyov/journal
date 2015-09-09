
#include <JournalDM_Model.h>
#include <JournalDM_Category.h>

int main( int argc, char** argv )
{
  QString aProjectDir = getenv( "PROJECT_DIR" );
  JournalDM_Model aModel;
  aModel.Load( aProjectDir + "/examples/german.txt" );
  printf( "Model is loaded\n" );
  int n = aModel.GetNbCategories();
  printf( "The number of categories: %i\n", n );
  for( int i=0; i<n; i++ )
  {
    std::string aName = aModel.GetCategory( i )->GetName().toStdString();
    printf( "Category '%s':\n", aName.c_str() );
    printf( "  Number of lines: %i\n", aModel.GetCategory( i )->GetNbLines( true ) );
  }

  return 0;
}
