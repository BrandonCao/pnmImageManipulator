/*
 sink.h
 Brandon Cao

 
 */

#include "image.h"
#ifndef SINK_H
#define SINK_H

class Sink
{
public:
    Sink(); // default constructor
//    virtual ~Sink(); // virtual destructor to make sure right destructer is called
    void SetInput(Image *i); // set input1 pointer
    void SetInput2(Image *i2);  //set input 2 pointer

    
    virtual const char *SinkName() = 0;

    
protected:
    
      const Image *input;
      const Image *input2;
};

#endif