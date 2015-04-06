


#define SIZE 256

#define SIZE_OF_FILE_BLOCK (SIZE + sizeof(int) + sizeof(int) + sizeof(mode_t))


typedef struct _file_block 
{
	int size_before;
	int size_after;
	char path[SIZE];
	mode_t st_mode;
}file_block;

int compressFile( int fd, char **dest);
void makeFileWrapper(char *dest, file_block *fb );
void makeFileBlockStruct( file_block *dest, struct stat *source );
int getFileSizeAfter( char *source);
