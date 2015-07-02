/*
 
 PNMwriter.h
 Brandon  Cao

 
 */

#include <stdio.h>
#include "sink.h"

#ifndef PNMWRITER_H
#define PNMWRITER_H

class PNMwriter : public Sink
{
public:
    void Write(char *f);
    const char * SinkName();
};

#endif
