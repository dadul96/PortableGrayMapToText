#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void generateTextFile(char* pInFileName, char* pOutFileName);


int main() {
	char inFileName[] = "input.pgm";
	char outFileName[] = "output.txt";

	generateTextFile(inFileName, outFileName);

	return 0;
}


void generateTextFile(char* pInFileName, char* pOutFileName) {
	FILE* inputFile;
	FILE* outputFile;

	fopen_s(&inputFile, pInFileName, "rt");
	fopen_s(&outputFile, pOutFileName, "wt");

	if (inputFile == NULL)
	{
		perror("ERROR: The input file could not be opened!");
	}
	else
	{
		if (outputFile == NULL)
		{
			perror("ERROR: The output file could not be opened!");
		}
		else
		{
			const int LF_ASCII = 10;		//ASCII value for Line Feed
			const int OFFSET_ASCII = 48;	//ASCII number offset
			int inCharValue = 0;
			int tempCharValue = 0;
			int outCharValue = 0;
			int lineCount = 0;
			int digitCount = 0;

			do
			{
				inCharValue = fgetc(inputFile);
				if (lineCount < 3)	//ignoring the first 3 lines (header of .pgm)
				{
					if (inCharValue == LF_ASCII)
					{
						lineCount++;
					}
				}
				else
				{
					if (inCharValue >= OFFSET_ASCII && inCharValue <= (OFFSET_ASCII + 9))
					{
						inCharValue = inCharValue - OFFSET_ASCII;
						if (digitCount != 0)
						{
							tempCharValue = (tempCharValue * 10) + inCharValue;	//create number from single digits
						}
						else
						{
							tempCharValue = inCharValue;
						}
						digitCount++;
					}
					else
					{
						if (digitCount != 0)
						{
							outCharValue = (tempCharValue - 1) / 2;	//Algorithm to map the values from 1-255 to 0-127
							fprintf_s(outputFile, "%c", outCharValue);
							digitCount = 0;
						}
					}
				}
			} while (inCharValue != EOF);
			fclose(inputFile);
			fclose(outputFile);
		}
	}
}