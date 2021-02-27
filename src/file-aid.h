#include <unistd.h> 
#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 
#include <fcntl.h>
#include <sys/stat.h> 
#include "../errcheck.h"


//Goals - file aiding helper functions 
// for using standard file opening methods. 
// -read only open
// -create new file
// -open for appending and writing 
// -open for writing (overwirte)
//
// These methods also perform error checking. 

//Function prototypes
int r_open(char *); 
int n_open(char *); 
int a_open(char *); 
int w_open(char *); 

// Read Only open
int r_open(char *pathname) { 
	int fd; // file descriptor

	fd = open(pathname, O_RDONLY); 
	if(fd == -1) {
		fatal("Opening File"); 
		return -1; 
	}
	
	return fd;
}

// Create new file
int a_open(char *pathname) { 
	int fd; // file descriptor

	fd = open(PATHNAME, O_WRONLY|O_CREAT|O_APPEND);
	if(fd == -1) {
		fatal("Opening write file"); 
		return -1; 
	}
	return fd; 
}

// overwirte open
int w_open(char *pathname) { 
	int fd; // File descriptor

	fd = open(pathname, O_WRONLY); 
	if(fd == -1) { 
		fatal("opening overwtite file"); 
		return -1; 
	}
	return fd; 
}




