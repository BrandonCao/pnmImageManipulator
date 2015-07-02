/*
 source.C
 Brandon Cao

 
 */

#include <stdio.h>
#include "image.h"
#include "source.h"
#include "logging.h"

Image * Source::GetOutput()
{
    
    return &output;
}



void Source::Update()
{
    char msg[128];
    sprintf(msg, "%s: about to execute", SourceName());
    Logger::LogEvent(msg);
    Execute();
    sprintf(msg, "%s: done executing", SourceName());
    Logger::LogEvent(msg);
    

}



Source::Source() /*initializer*/
{
    
    output.SetSource(this);
    
}
