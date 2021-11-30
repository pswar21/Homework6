/*
 *     * Filename      CDKexample.cc
 *         * Date          4/29
 *             * Author        Priyanshu 
 *                 * Email         pxs170020@utdallas.edu
 *                     * Course        CS 3377.502 Spring 2020
 *                         * Version       1.0  (or correct version)
 *                             * Copyright 2020, All Rights Reserved
 *                                 *
 *                                     * Description
 *                                         *
 *                                             *     This is the main file that compiles the matrix and displays it 
 *                                                 *     
 *                                                     */

	
#include "display.h"
#include <sstream>
#include <iostream>
#include <stdint.h>
#include <fstream>
#include <cstring>     
#include <string>
#include "cdk.h"

#define MATRIX_WIDTH 5
#define MATRIX_HEIGHT 3
#define BOX_WIDTH 20
#define MATRIX_NAME_STRING "Binary File Contents"

const int maxRecordStringLength = 25;

using namespace std;

class BinaryFileHeader
{
	public: 
	uint32_t magicNumber;
	uint32_t versionNumber;
	uint64_t numRecords; 
};

class BinaryFileRecord 
{
	public:
	uint8_t         strLength;
    	char		stringBuffer[maxRecordStringLength];
};	
     


int main()
{

  WINDOW	*window;
  CDKSCREEN	*cdkscreen;
  CDKMATRIX     *myMatrix;           // CDK Screen Matrix

  const char 		*rowTitles[MATRIX_HEIGHT+1] = {"r0", "a", "b", "c"};
  const char 		*columnTitles[MATRIX_WIDTH+1] = {"C0", "a", "b", "c", "d", "e"};
  int		boxWidths[MATRIX_WIDTH+1] = {BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH};
  int		boxTypes[MATRIX_WIDTH+1] = {vMIXED, vMIXED, vMIXED, vMIXED, vMIXED, vMIXED};

  /*
   * Initialize the Cdk screen.
   *
   * Make sure the putty terminal is large enough
   */
  window = initscr();
  cdkscreen = initCDKScreen(window);

  /* Start CDK Colors */
  initCDKColor();

  /*
   * Create the matrix.  Need to manually cast (const char**) to (char **)
  */
  myMatrix = newCDKMatrix(cdkscreen, CENTER, CENTER, MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_WIDTH, MATRIX_HEIGHT,
			  MATRIX_NAME_STRING, (char **) columnTitles, (char **) rowTitles, boxWidths,
				     boxTypes, 1, 1, ' ', ROW, true, true, false);

  if (myMatrix == NULL)
    {
      errormsg();
      printf("The matrix was the problem");
      _exit(1);
    }

  /* Display the Matrix */
  drawCDKMatrix(myMatrix, true);
  

  BinaryFileHeader *myHeader = new BinaryFileHeader(); 


  ifstream binInHeader("/scratch/perkins/cs3377.bin", ios:: in | ios:: binary); 

  if(binInHeader.is_open() == false){
	errormsg(); 
  }

  string out;
  stringstream con; 

  binInHeader.read((char*) myHeader, sizeof(BinaryFileHeader));
  
  con << "Magic: 0x" << hex << uppercase << myHeader->magicNumber; //converts to hexstring from unsingn
  out = con.str();
  setCDKMatrixCell(myMatrix, 1, 1, out.c_str()); // for 
  con.str(""); //formatting 
  con << "Version: " << dec << myHeader->versionNumber;
  out = con.str();
  setCDKMatrixCell(myMatrix, 1, 2, out.c_str());
  con.str("");
  con << "NumRecords: " << myHeader->numRecords;
  out = con.str();
  setCDKMatrixCell(myMatrix, 1, 3, out.c_str());

  long int position = sizeof(BinaryFileHeader); //gets size of header 
  BinaryFileRecord *myRecord = new BinaryFileRecord();
 
  binInHeader.read((char*) myRecord, sizeof(BinaryFileRecord));
  if(binInHeader.is_open() == false){
          errormsg();
    }
    
  binInHeader.seekg(position); //move the cursor
    
    int counter = 2; 
    while(counter <= MATRIX_WIDTH){
    if(!binInHeader.eof()){
       binInHeader.read((char*) myRecord, sizeof(BinaryFileRecord));
       con.str("");
       con << "strlen: " << strlen(myRecord->stringBuffer);
       out = con.str();
       setCDKMatrixCell(myMatrix, counter, 1, out.c_str());
       setCDKMatrixCell(myMatrix, counter, 2, myRecord -> stringBuffer);
       }
       counter+=1;
     }
						     
  /*
   * Dipslays a message
   */
 // setCDKMatrixCell(myMatrix, 2, 2, "Test Message");
 
  drawCDKMatrix(myMatrix, true);    /* required  */

  /* so we can see results */
  string read;
  cin >> read; 
  

  // Cleanup screen
  endCDK();
}
