/*
 
 PNMreader.h
 Brandon  Cao

 
 */
#include <stdio.h>
#include "source.h"

#ifndef PNMREADER_H
#define PNMREADER_H

class PNMreader : public Source
{
public:
    PNMreader(const char *filename);
    virtual ~PNMreader();
    virtual void Execute();
    const char *SourceName();
    
protected:
    char* filename;
};

#endif