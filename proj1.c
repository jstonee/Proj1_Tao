#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// remove duplicate characters in array word and return the result string
char * removeDuplicates(char word[]);

// search the first num characters in array charArray for character target
// return a non-zero integer if found, otherwise, return 0
int targetFound(char charArray[], int num, char target);

// initialize the encrypt array with appropriate cipher letters according to the given key
void initializeEncryptArray(char key[], char encrypt[]);

// initialize the decrypt array with appropriate substitute letters based on the encrypt array
void initializeDecryptArray(char encrypt[], char decrypt[]);

// process data from the input file and write the result to the output file
// pass the encrypt array to parameter substitute if encryption is intended
// pass the decrypt array to parameter substitute if decryption is intended
void processInput(FILE * inf, FILE * outf, char substitute[]);

int main(int argc, char* argv[])
{
	int choice;
	char *key;
	key = (char*)malloc(sizeof(char));
	char *fixedKey;
	fixedKey = (char*)malloc(sizeof(char)* 26);
	char encrypt[26], decrypt[26];
	FILE *fin, *fout;

	if (argc != 5)
	{
		printf("Usage: cipher option key infile, outfile\n");
		printf("Option 1 for encryption and 2 for decryption\n");
		exit(1);
	}

	choice = atoi(argv[1]);
	key = argv[2];
	int length = strlen(key);
	char *tempKey = (char*)malloc(length + 26);
	int i = 0;
	for (i; i < (length + 26); i++)
	{
		if (i < length)
			*(tempKey + i) = *(key + i);
		else
			*(tempKey + i) = 'Z' - (i - length);
	}

	fin = fopen(argv[3], "r");
	fout = fopen(argv[4], "w");

	if (fin == NULL || fout == NULL)
	{
		printf("File could not be opened\n");
		exit(1);
	}

	fixedKey = removeDuplicates(tempKey);
	initializeEncryptArray(fixedKey, encrypt);
	
	fclose(fin);
	fclose(fout);

	return 0;
}

char * removeDuplicates(char word[])
{
	int i = 0, j = 0;
	char  *temp = (char*)malloc((sizeof(char) * 26));
	char ch;
	int alpha[256] = { 0 };

	for (i; i < strlen(word); i++)
	{
		ch = word[i];
		if (alpha[ch] == 0)
		{
			alpha[ch] = 1;
			*(temp + j) = ch;
			j++;
		}
		if (j == 26)
			break;

	}
	return temp;
}

void initializeEncryptArray(char key[], char encrypt[])
{
	int i = 0;
	for (i; i < 26; i++)
	{
		encrypt[i] = key[i];
	}
}