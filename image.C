/*
 image.C
 Brandon Cao

 
 */


#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "image.h"
#include "source.h"



Image::Image(void){
    src = NULL;
    h= 0;
    w= 0;
    data = NULL;

}


Image::~Image(){
    delete [] data;
}


Image::Image(int width, int height){
    w = width;
    h = height;
    data = (unsigned char *) malloc(h*w*3);
    src = NULL;
}

Image::Image(Image &i){
    w = i.w;
    h = i.h;
    data = i.data;
    src = NULL;
}

void Image::SetSource(Source *source)
{
    src = source;
}


void Image::Update() const
{
    if(src !=NULL){
        src->Update();
    }
    
}


int Image::GetHeight()const {
    return h;
}

int Image::GetWidth()const {
    return w;
}

void Image::ResetSize(int width, int height)
{
    w = width;
    h = height;
    delete [] data;
    data = new unsigned char[3*w*h];
}



unsigned char * Image::GetPixel(int width, int height)const{
    
    return data+3*(height*w+width);
    
}

void Image::SetPixel(int width, int height, unsigned char *pixel){
    //height*w+width = indexing the image
    data[3*(height*w+width)+0] = pixel[0]; 
    data[3*(height*w+width)+1] = pixel[1];
    data[3*(height*w+width)+2] = pixel[2];
    
}




