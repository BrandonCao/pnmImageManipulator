/*
 
 filter.C
 Brandon Cao

 
 */

#include "filter.h"
#include "logging.h"



int sumException;

void Filter::Update(){
    
    
    if(input != NULL){
        
        char msg[128];
        sprintf(msg, "%s: about to update input1", SinkName());
        Logger::LogEvent(msg);
        input->Update();
        sprintf(msg, "%s: done updating input1", SinkName());
        Logger::LogEvent(msg);
        sprintf(msg,"%s: about to execute", SinkName() );
        Logger::LogEvent(msg);
        sprintf(msg,"%s: done executing", SinkName() );
        Logger::LogEvent(msg);

    }
    
    if(input2 != NULL){
        
        char msg[128];
        sprintf(msg, "%s: about to update input2", SinkName());
        Logger::LogEvent(msg);
        input2->Update();
        sprintf(msg, "%s: done updating input2", SinkName());
        Logger::LogEvent(msg);
        sprintf(msg,"%s: about to execute", SinkName() );
        Logger::LogEvent(msg);
        sprintf(msg,"%s: done executing", SinkName() );
    }
    
    Execute();
    
}



const char *Filter::SourceName() { return FilterName(); };
const char *Filter::SinkName() { return FilterName(); };
