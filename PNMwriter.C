/*
 
 PNMwriter.C
 Brandon  Cao

 
 */

#include "PNMwriter.h"
#include <stdio.h>
#include <string.h>
#include <iostream>
#include "logging.h"

void PNMwriter::Write(char *filename)
{
    FILE *file = fopen(filename, "wb");
    
     fprintf(file, "P6\n%d %d\n%d\n", input->GetWidth(), input->GetHeight(), 255);
    
    fwrite(input->Getdata(), sizeof(unsigned char), input->GetWidth() * input->GetHeight()*3, file);
    
    fclose(file);
    
    
}


const char * PNMwriter::SinkName()
{
    const char *msg;
    msg = "PNMwriter";
    return msg;
}

