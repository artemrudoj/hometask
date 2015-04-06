#include "defines.h"
#include <libgen.h>


#define COMPRESSION_TYPE Z_DEFAULT_COMPRESSION

int compressFile( int fd, char **dest, char *path)
{
	struct stat info;
	file_block fb;
	char *mappedFile;
	if ( fstat( fd, &info) == -1 )
		RETURN_ERROR("fstat error", -1);
	mappedFile = mapFileToMemory( fd, &info);
	if ( mappedFile == NULL)
		RETURN_ERROR("mapFileToMemory error", -1);
	*dest = malloc( info.st_size + SIZE_OF_FILE_BLOCK);
	if ( *dest == NULL)
		RETURN_ERROR("malloc error", -1);
	makeFileBlockStruct( &fb, &info, path);
	int ret = mycompress( mappedFile, &(*dest)[SIZE_OF_FILE_BLOCK], COMPRESSION_TYPE , &fb);
	if (ret != Z_OK)
	{
		free( *dest);
		RETURN_ERROR("compress error", -1);
	}
	makeFileWrapper( *dest, &fb );
	getFileSizeAfter(*dest);
	ret = munmap(mappedFile, info.st_size );
	if ( ret == -1 )
	{
		free( *dest);
		RETURN_ERROR("munmap error", -1);
	}
	return 0;
}

int decompressFile( char *source )
{
	file_block  fb;
	parseFileBlock( source, &fb);
	char *dest = (char *) malloc ( fb.size_before + SIZE_OF_FILE_BLOCK );
	if ( dest == NULL)
		RETURN_ERROR("malloc error", -1);
	int ret = mydecompress( source + SIZE_OF_FILE_BLOCK, dest , &fb);
	if (ret != Z_OK)
	{
		free( dest);
		RETURN_ERROR("decompress error", -1);
	}
	int fd;
	fd = open( basename(fb.path), O_RDWR | O_CREAT, 0777);
	write( fd, dest, fb.size_before );
	return 0;
}

void makeFileWrapper(char *dest, file_block *fb )
{

	memcpy( dest, &fb->size_before, sizeof(fb->size_before));
	memcpy( dest + sizeof(fb->size_before), &fb->size_after, sizeof(fb->size_after));
	memcpy( dest + sizeof(fb->size_before) + sizeof(fb->size_after), fb->path, SIZE);
	memcpy( dest + sizeof(fb->size_before) + sizeof(fb->size_after) + SIZE, &fb->st_mode, sizeof(fb->st_mode));

	ALOGD("makeFileWrapper: size_before = %d", *(size_t *)(dest));
	ALOGD("makeFileWrapper: size_after = %d",  *(size_t *)(dest + sizeof(fb->size_before)));
	ALOGD("makeFileWrapper: path = %s", (dest + sizeof(fb->size_before) + sizeof(fb->size_after)));
	ALOGD("makeFileWrapper: st_mode = %d", *(mode_t *)(dest + sizeof(fb->size_before) + sizeof(fb->size_after) + SIZE));
}


void makeFileBlockStruct( file_block *dest, struct stat *source, char *path )
{
	dest->size_before = source->st_size;
	dest->st_mode = source->st_mode;
	strcpy(dest->path, path);
}

int getFileSizeAfter( char *source)
{
	return *(int *)(source + sizeof(size_t));
}

int getFileSizeBefore( char *source)
{
	return *(int *)(source);
}

char *getFilePath( char *source)
{
	return source + sizeof(size_t) + sizeof(size_t);
}

mode_t getFileMode( char *source)
{
	return *(mode_t *)(source + sizeof(size_t) + sizeof(size_t) + SIZE);
}

void parseFileBlock( char *source, file_block *fb)
{
	fb->size_before = getFileSizeBefore( source);
	fb->size_after = getFileSizeAfter( source);
	strcpy(fb->path, getFilePath( source));
	fb->st_mode = getFileMode( source);
}
