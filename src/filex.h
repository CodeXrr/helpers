// Helper functions when working with files. 

// Open a file for rdonly
int ec_open(char *filepath) { 
	int fd = open(filepath, O_RDONLY); 
	if(fd == -1) {
		printf("[!!] Failed to open file \'%s\'\n", filepath); 
		exit(-1); 
	}
	return fd; 
}

// Count number of bytes in a file. 
int filesize(char *filepath) { 
	unsigned char byte; 
	int count=0, fd = ropen(filepath); 

	while(read(fd, &byte, 1) == 1)
		count++; 

	close(fd); 
	return count; 
}
	
