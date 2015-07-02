/*
 
 sink.C
 Brandon Cao

 
 */
#include "sink.h"
#include <stdio.h>

Sink::Sink()
{
    input = NULL;
    input2 = NULL;
}

void Sink::SetInput(Image  *image1)
{
    this->input = image1;
}

void Sink::SetInput2(Image *image2)
{
    this->input2 = image2;
}


//Sink::~Sink()
//{
//    
//    
//}


