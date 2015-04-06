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
		ret = compressFile( fd, &compressed);
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
	else
		printf(" Incorrect arguments\n");
	return 0;
}
/*
    else if (argc == 3 && (strcmp(argv[1], "-d") == 0)) {
        ret = inf(stdin, stdout);
        if (ret != Z_OK)
            zerr(ret);
        return ret;
    }

    /* otherwise, report usage 
    else {
        fputs("zpipe usage: zpipe [-d] < source > dest\n", stderr);
        return 1;
    }
}
	

//decompressing
	file_size info_dec;
	mappedFile = mapFileToMemory( fdout, &info_dec);
	compressedFile = malloc( info.before_size);
	if ( compressedFile == NULL)
	{	
		close(fdout);
		RETURN_ERROR("malloc error", -1);
	}
	ret = mydecompress( mappedFile, compressedFile, &info);
	ALOGD("ret = %d", ret);
	if (ret != Z_OK)
	{
	    close(fdout);
	    free( compressedFile);
            RETURN_ERROR("compress error", -1);
	}
	fd = open( "_1.txt", O_RDWR | O_CREAT, 0777);
	ALOGD("info.before_size = %d", info.before_size);
	write( fd, compressedFile, info.before_size);
	close(fd);
	close(fdout);



	close(fd);
	close(fdout);
	free(compressedFile);
        return ret;
}*/
