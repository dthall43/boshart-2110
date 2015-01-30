#if !defined READ_FILE
#define READ_FILE

#include "Text.h"

#include <fstream>
using namespace std;

class ReadFile
{
	public:
	   ReadFile(const char* file_name);
	   ~ReadFile();
	   void destroyReadFile(/*ReadFile* rf*/);
	   String* readLine(/*ReadFile* rf*/);
	   bool eof(/*ReadFile* rf*/);
	   void close(/*ReadFile* rf*/);
	private:
	   ifstream input_file;
	   bool _eof;
	   bool closed;
  
};



#endif
