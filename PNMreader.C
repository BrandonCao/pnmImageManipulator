/*
 
 PNMreader.C
 Brandon  Cao
 project 3G
 
 */

#include "PNMreader.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include "logging.h"

PNMreader::PNMreader(const char *f) /*filename passed via constructer*/
{
    filename = new char[strlen(f)+1];
    strcpy(filename, f);
}

PNMreader::~PNMreader() //deconstructer
{
    delete [] filename;
}



void PNMreader::Execute()
{
    FILE *file = fopen(this->filename, "rb");
    char magicNum[128];
    int  height, width, maxval;
    
    if(file == 0){
        fprintf(stderr, "Unable to open file %s", this->filename);
        exit(0);
    }
    
    fscanf(file, "%s\n%d %d\n%d\n", magicNum, &width, &height, &maxval);
    
    output.ResetSize(width, height); /*reset width and height to the size of input image along with allocatting more memory. */
    
    unsigned char *data = output.Getdata();
    fread(data, sizeof(char), 3*width*height, file);
    
    fclose(file);
}


const char * PNMreader::SourceName()
{
    const char *msg;
    msg = "PNMreader";
    return msg;
}
    
