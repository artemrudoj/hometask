#include "defines.h"


int main( int argc, char **argv)
{
	if (argc == 3 && (strcmp(argv[1], "-c") == 0)) 
	{
		file_size info;
		if ( init_log( A, "map.log") == -1)
		{
			shm_unlink( SHAREDMEM_FILENAME);
			return -1;
		}
		int fd = open( argv[2] , O_RDWR,  0777);
		char *compressed;
		int ret;
		ret = compressFile( fd, &compressed, argv[2]);
		if( ret != 0 )
			RETURN_ERROR( "comressFile", -1 );
		int afterSize = getFileSizeAfter( compressed);
		ALOGD("afterSize = %d", afterSize);
		char name[20];
		strcpy( name, argv[2]);
		strcat( name, ".arch");
		close(fd);
		fd = open( name, O_RDWR | O_CREAT, 0777);
		int len;
		len = write( fd, compressed, afterSize + sizeof(file_block));
		close(fd);
		//free(compressed);
	}
	else if (argc == 3 && (strcmp(argv[1], "-d") == 0)) 
	{
		if ( init_log( A, "map.log") == -1)
		{
			shm_unlink( SHAREDMEM_FILENAME);
			return -1;
		}
		int fd = open( argv[2] , O_RDWR,  0777);
		struct stat info;
		file_block fb;
		char *mappedFile, *dest;
		mappedFile = mapFileToMemory( fd, &info);
		if ( mappedFile == NULL)
			RETURN_ERROR("mapFileToMemory error", -1);
		int ret =  decompressFile( mappedFile, &dest);
		if( ret != 0 )
			RETURN_ERROR( "decomressFile", -1 );
		close(fd);
		fd = open( basename(getFilePath(mappedFile)), O_RDWR | O_CREAT, 0777);
		write( fd, dest, getFileSizeBefore(mappedFile) );
		close(fd);
		free(dest);
	}
	else
		printf(" Incorrect arguments\n");
	return 0;
}
