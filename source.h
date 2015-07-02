/*
 
source.h
Brandon Cao

 
*/

#include "image.h"

#ifndef SOURCE_H
#define SOURCE_H

class Source
{
    
protected:
    Image output; //Image object
    virtual void Execute()=0;
    
public:
    Image * GetOutput(); /*at returns a pointer to its Image data member.*/
    virtual const char *SourceName() = 0;
    virtual void Update();
    void SetSource();
    Source();

};
#endif