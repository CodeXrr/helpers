#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 
#include <unistd.h>
#include <ctype.h>

// A helper function to find the next char from 
// a given offset of a string. Returns the index 
// which the targetChar was found at. 
// PARAMETERS: Read Buffer, char to find, starting offset
int findNext(char *strBuffer, char targetChar, int offset) {
	int i; //Index
	int strLength = strlen(strBuffer); 
	char byte; 

	// Validate offset
	if(offset < 0 || offset >= strLength) {
		printf("[!!] Invalid offset parameter\n"); 
		return -1; 
	}

	for(i=offset; i < strLength; i++) {
		byte = strBuffer[i]; 
		if(byte == targetChar)
			return i + 1;  // Adding one cause we return before the inc
	}

	// No matching char found.
	return -1; 
}

// Validate the format of an IP address from the supplied string. 
// Returns 0 if false and 1 if true. 
int validIpFormat(char *string) {
	int pos, nextPos; 
	int diff; 

	// Find first period
	pos = findNext(string, '.', 0); 
	printf("[DEBUG] POS1: %d\n", pos); 
	if(pos > 4)
		return 0; 

	diff = pos; 
	printf("diff %d\n", diff);

	// Find second period
	nextPos = findNext(string, '.', pos); 
	printf("[DEBUG] POS2: %d\n", nextPos); 
	printf("diff - nextpos == %d\n", (nextPos-diff)); 
	// Check range
	if((nextPos-diff) > 4 || (nextPos-diff) <= 1)
		return 0; 
	
	diff = nextPos;
	printf("diff %d\n", diff);

	// Find third period
	pos = findNext(string, '.', nextPos); 
	printf("[DEBUG] POS3: %d\n", pos); 
	printf("diff - pos == %d\n", (pos-diff)); 

	if((pos-diff) > 4 || (pos-diff) <= 1)
		return 0; 

	return 1; 
	
}

int countChar(char *data, char targetChar) {
	int strLength =  strlen(data); 
	int count= 0;
	char byte;

	for(int i = 0; i < strLength; i++) {
		byte = data[i]; 
		if(byte == targetChar)
			count++; 
	}; 

	return count; 
}

int hasAlpha(char *string) { 
	int strLength = strlen(string); 
	char byte; 

	for(int i=0; i < strLength; i++) {
		byte = string[i]; 
		if(isalpha(byte))
			return 1; 
	}

	return 0; 
		
}

// Takes a sting and determies if the string is a IP address. 
// --[ IP ADDR String length range: MIN 7 - MAX 15
// 				  0.0.0.0 | 000.000.000.000
// 	*SHOULD CHECK FOR 
// 	 ANY ALPHA CHARs
//
// 	 *Final Check: Periods. Should always have 3.
// 	 			Should be in the 4 char range.
//
//
int isIp(char *string) {
	//---------------------------------------------------------
	// DATA TOOLS.
	// =====================/
	char octet[3]; // A small array that holds an IP's octet.
		       // allowing an address to be broken into
		       // octets.
	char byte;//<--- Temp byte buffer
	int pos_index = 0;  // Used to track the position in string.
        const int min_ip_range = 7;  // Constant value range.
	const int max_ip_range = 15; // Contant value range.
	int strlength = strlen(string); 
	int periodCount = 0;
	int foundPeriodFlag = 0; 

	// String length Range Test.
	if(strlength < 7 || strlength > 15)
		return 0; 

	// Check for illegal chars
	if(hasAlpha(string))
		return 0; 
	

	// Count periods
	if(countChar(string, '.') != 3)
		return 0; 
	

	// Validate Format
	if(validIpFormat(string))
		return 1; 

	
}

//=================================================================
// int isMac(char *)
//-----------------------------------------------------------------
// Requirments.
// 1. check length of string 
// 2. check char range
// 3. check format

#define MAC_LENGTH 17

int validMacFormat(char *string) { 
	int colonCount = 0; 
	
	// This loops verifys the correct number of colons 
	// and the correct placement. 
	for(int index = 0; index < strlen(string); index++) { 
		if((index%3) == 2) { 
			if(string[index] != ':')
				return 0; 
			else
				colonCount += 1; 
		}
	}
	printf("[DEBUG] colonCount == %d\n", colonCount); 
	if(colonCount == 5)
		return 1; 
	else 
		return 0; 
}

// returns 1 (true) if in range
// returns 0 (false) if NOT in range 
int inRange(char *string) { 
	// 0 - 9 ascii decimal range (48 - 57)
	// A - F ascii decimal range (65 - 70)
	char curChar; // Current char
	
	// Loop through and read every char
	// verify that all chars are in range, 
	// if not return false. 
	for(int index = 0; index < strlen(string); index++) { 
		curChar = string[index]; 
		if(curChar == ':')
			continue;
		if(curChar < 48 || curChar > 57) { // Check digit range
			printf("[DEBUG] \'%c\' out of 0-9 range\n", curChar); 

			if(curChar < 65 || curChar > 70) {
			printf("[DEBUG] \'%c\' - out of A-F range\n", curChar); 

			return 0; 
			}
		}
	}//exit loop

	// All characters passed and we made it this far so...
	// return true. 
	return 1; 
}

// returns 1 (true) if mac 
// returns 0 (false) if NOT mac
int isMac(char * string) { 
	//check string length
	if(strlen(string) != MAC_LENGTH) 
		return 0; 

	//check format
	if(validMacFormat(string) != 1) {
		printf("[DEBUG] \'%s\' format is NOT valid\n", string); 
		return 0; 
	}
	printf("[DEBUG] \'%s\' format is valid\n", string); 


	if(inRange(string) != 1) { 
		printf("[DEBUG] All chars are NOT in range\n"); 
		return 0; 
	}
	printf("[DEBUG] All char are in range\n"); 

	//All test passed
	printf("[DEBUG] all test passed..\n"); 
	return 1; 
}