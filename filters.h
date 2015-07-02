/*
 
 filters.h
 Brandon  Cao

 
 */
#include "filter.h"
#include <stdio.h>


#ifndef FILTERS_H
#define FILTERS_H



/****************************/
class Filters : public Filter
{

};
/****************************/

class Shrinker : public Filters
{
public:
    const char *FilterName();
    void Execute();
};


/****************************/

class LRConcat : public Filters
{
public:
    const char *FilterName();
    void Execute();
};

/****************************/
class TBConcat : public Filters
{
public:
    const char *FilterName();
    void Execute();
};

/****************************/
class Blender : public Filters
{
public:
    void Execute();
    void SetFactor(float f);
    const char *FilterName();
private:
    float factor;

};
/****************************/

class Crop : public Filters
{
public:
    Crop() { Istart = Istop = Jstart = Jstop = -1; };
    const char *FilterName();
    void   Execute();
    void SetRegion(int Istart_, int Istop_, int Jstart_, int Jstop_)
    {
        Istart = Istart_;
        Istop  = Istop_;
        Jstart = Jstart_;
        Jstop  = Jstop_;
    }
    
private:
    int Istart, Istop, Jstart, Jstop;
};

/****************************/

class Transpose : public Filters
{
public:
    const char * FilterName();
    void Execute();
};


/****************************/
class Invert : public Filters
{
public:
    const char * FilterName();
    void   Execute();
};

/****************************/

class Checkerboard : public Filters
{
public:
    const char *FilterName();
    void Execute();
};




/****************************/


class Color : public Source
{
protected:
    int width;  //size of image
    int height;
    unsigned char red; //color channels
    unsigned char green;
    unsigned char blue;
    
    
    
public:
    const char * SourceName();
    
    Color(int w, int h, unsigned char r, unsigned char g, unsigned char b)
    { //takes the parameters and assigns them to the variables in this class.
        //Produces image with the width, height and color channels 
        width = w;
        height = h;
        red = r;
        green = g;
        blue = b;
    };
    
    void   Execute();
};


/****************************/

class CheckSum : public Sink
{
public:
    void OutputCheckSum(const char *file);
    const char * SinkName();
};





#endif