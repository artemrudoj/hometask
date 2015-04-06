#include "defines.h"





int compressFile( int fd, char **dest)
{
	struct stat info;
	file_block fb;
	char *mappedFile;
	if ( fstat( fd, &info) == -1 )
		RETURN_ERROR("fstat error", -1);
	mappedFile = mapFileToMemory( fd, &info);
	*dest = malloc( info.st_size + SIZE_OF_FILE_BLOCK);
	if ( *dest == NULL)
		RETURN_ERROR("malloc error", -1);
	makeFileBlockStruct( &fb, &info);
	int ret = mycompress( mappedFile, &(*dest)[SIZE_OF_FILE_BLOCK], Z_DEFAULT_COMPRESSION , &fb);
	if (ret != Z_OK)
	{
		free( *dest);
		RETURN_ERROR("compress error", -1);
	}
	makeFileWrapper( *dest, &fb );
	getFileSizeAfter(*dest);
	return 0;
}

void makeFileWrapper(char *dest, file_block *fb )
{
	ALOGD("makeFileWrapper:fb->size_before = %d",fb->size_before);
	memcpy( dest, &fb->size_before, sizeof(int));
	memcpy( dest + sizeof(int), &fb->size_after, sizeof(int));
	printf("after = %d\n", *(int *)(dest+ sizeof(int)));
	memcpy( dest + sizeof(int) + sizeof(int), fb->path, SIZE);
	printf("after = %d\n", *(int *)(dest+ sizeof(int)));
	memcpy( dest + sizeof(int) + sizeof(int) + SIZE, &fb->st_mode, sizeof(mode_t));
}


void makeFileBlockStruct( file_block *dest, struct stat *source )
{
	dest->size_before = source->st_size;
	dest->st_mode = source->st_mode;
}

int getFileSizeAfter( char *source)
{
	ALOGD("getFileSizeAfter: size_after = %d",*(int *)(source+ sizeof(int)));
	return *(int *)(source+ sizeof(int));
}
