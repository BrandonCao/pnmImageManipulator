/*
 
 filters.C
 Brandon  Cao

 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "filters.h"
#include <iostream>
#include "logging.h"

void Shrinker::Execute()
{
    
    if(input == NULL)
    {
        char msg[128];
        sprintf(msg, "%s: no input!", FilterName());
        DataFlowException e(FilterName(),msg);
        throw e;
        
    }
    
    output.ResetSize((input->GetWidth()/2), (input->GetHeight()/2));
    
    std::cerr << "width after Shrinker: " << output.GetWidth() << " *** height after Shrinker " << output.GetHeight() << std::endl;
    
    for (int w=0; w < output.GetWidth(); w++)
        /*sets pixels[i][j] of output to equal pixel[i*2][j*2] of input*/
    {
        for (int h=0; h < output.GetHeight(); h++)
        {
            unsigned char *p = input->GetPixel(2*w, 2*h);
            output.SetPixel(w, h, p);
        }
    }
}

const char *Shrinker::FilterName(){
    return "Shrinker";
}



/******************************************************/

void LRConcat::Execute()
{

    if(input == NULL)
    {
        char msg[128];
        sprintf(msg, "%s: no input!", FilterName());
        DataFlowException e(FilterName(),msg);
        throw e;
        
    }
    
    if(input2 == NULL)
    {
        char msg[128];
        sprintf(msg, "%s: no input2!", FilterName());
        DataFlowException e(FilterName(),msg);
        throw e;
    }
    
    if(input->GetHeight() != input2->GetHeight())
    {
        char msg[1024];
        sprintf(msg, "%s: heights must match: %d, %d", FilterName(), input->GetHeight(), input2->GetHeight());
        DataFlowException e(FilterName(), msg);
        throw e;
    }
    
    int l_width = input->GetWidth();
    int r_width = input2->GetWidth();
    int l_height = input->GetHeight();
    int r_height = input2->GetHeight();
    
    
    output.ResetSize(l_width + r_width, std::max(l_height, r_height));
    
    std::cerr << "width after LRCONCAT: " << output.GetWidth() << " *** height after LRCONCAT: " << output.GetHeight() << std::endl;
    
    for (int w = 0; w < l_width; w++)
    {
        for (int h = 0; h < l_height; h++)
        {
            unsigned char *p = input->GetPixel(w, h);
            output.SetPixel(w, h, p);
        }
    }
    
    for (int w = 0; w < r_width; w++)
    {
        for (int h = 0; h < r_height; h++)
        {
            unsigned char *p = input2->GetPixel(w, h);
            output.SetPixel((l_width + w), h, p);
        }
    }
}

const char *LRConcat::FilterName(){
    return "LRConcat";
}


/******************************************************/

void TBConcat::Execute()
{

    
    if(input == NULL)
    {
        char msg[128];
        sprintf(msg, "%s: no input!", FilterName());
        input->Update();
        DataFlowException e(FilterName(),msg);
        throw e;

    }
    
    if(input2 == NULL)
    {
        char msg[128];
        sprintf(msg, "%s: no input2!", FilterName());
        input2->Update();
        DataFlowException e(FilterName(),msg);
        throw e;
    }
    
    if(input->GetWidth() != input2->GetWidth())
    {
        char msg[1024];
        sprintf(msg, "%s: widths must match:%d, %d", FilterName(), input->GetWidth(),input2->GetWidth());
        DataFlowException e(FilterName(),msg);
        throw e;

    }

    
    int t_width = input->GetWidth();
    int b_width = input2->GetWidth();
    int t_height = input->GetHeight();
    int b_height = input2->GetHeight();
    output.ResetSize(std::max(t_width, b_width), t_height + b_height);
    
    std::cerr << "width after BCONCAT: " << output.GetWidth() << " *** height after BCONCAT: " << output.GetHeight() << std::endl;
    
    
    for (int w = 0; w < t_width; w++)
    {
        for (int h = 0; h < t_height; h++)
        {
            unsigned char *p = input->GetPixel(w, h);
            output.SetPixel(w, h, p);
        }
    }
    
    for (int w = 0; w < b_width; w++)
    {
        for (int h = 0; h < b_height; h++)
        {
            unsigned char *p = input2->GetPixel(w, h);
            output.SetPixel(w, (t_height + h), p);
        }
    }
}

const char *TBConcat::FilterName(){
    return "TBConcat";
}

/******************************************************/

void Blender::SetFactor(float f)
{
    this->factor = f;
}

void Blender::Execute()
{
    
    if(input == NULL)
    {
        char msg[128];
        sprintf(msg, "%s: no input!", FilterName());
        input->Update();
        DataFlowException e(FilterName(),msg);
        throw e;

        
    }
    
    if(input2 == NULL)
    {
        char msg[128];
        sprintf(msg, "%s: no input2!", FilterName());
        input2->Update();
        DataFlowException e(FilterName(),msg);
        throw e;
    }
    
    if(factor < 0 || factor > 1)
    {
        char msg[1024];
        sprintf(msg, "%s: factor does not work: %f", FilterName(), factor);
        DataFlowException e(FilterName(), msg);
        throw e;
    }
    else{
        int width = input->GetWidth();
        int height = input->GetHeight();
        
        output.ResetSize(width, height);
        
        std::cerr << "width after Blender: " << output.GetWidth() << " *** height after Blender: " << output.GetHeight() << std::endl;
        
        for (int w = 0; w < width; w++)
        {
            for (int h = 0; h < height; h++)
            {
                unsigned char red = (input->GetPixel(w, h)[0]*factor) + (input2->GetPixel(w, h)[0]*(1-factor));
                unsigned char green = ((input->GetPixel(w, h)[1]*factor) + (input2->GetPixel(w, h)[1]*(1-factor)));
                unsigned char blue =  ((input->GetPixel(w, h)[2]*factor) + (input2->GetPixel(w, h)[2]*(1-factor)));
                unsigned char pixel[] = {red, green, blue};
                output.SetPixel(w, h, pixel);
            }
        }
    }
}

const char *Blender::FilterName(){
    return "Blender";
}


/******************************************************/

void Crop::Execute() 
{
    if (Istart < 0 || Istop < 0 || Jstart < 0 || Jstop < 0)
    {
        char msg[1024];
        sprintf(msg, "%s: uninitialized region", FilterName());
        DataFlowException e(FilterName(), msg);
        throw e;
    }
    if (Istart >= input->GetWidth() || Istop >= input->GetWidth())
    {
        char msg[1024];
        sprintf(msg, "%s: region outside image width", FilterName());
        DataFlowException e(FilterName(), msg);
        throw e;
    }
    if (Jstart >= input->GetHeight() || Jstop >= input->GetHeight())
    {
        char msg[1024];
        sprintf(msg, "%s: region outside image height", FilterName());
        DataFlowException e(FilterName(), msg);
        throw e;
    }
    if (Istop < Istart || Jstop < Jstart)
    {
        char msg[1024];
        sprintf(msg, "%s: invalid region", FilterName());
        DataFlowException e(FilterName(), msg);
        throw e;
    }
    
    int height = Jstop-Jstart+1;
    int width  = Istop-Istart+1;
    int inputWidth = input->GetWidth();
    
    
    output.ResetSize(width, height);
    
    
    unsigned char *buffer = output.Getdata();
    const unsigned char *buffer1 = input->Getdata();
    for (int i = Istart ; i <= Istop ; i++)
        for (int j = Jstart ; j <= Jstop ; j++)
        {
            int idx1 = j*inputWidth+i;
            int idx  = (j-Jstart)*width+(i-Istart);
            buffer[3*idx]   = buffer1[3*idx1];
            buffer[3*idx+1] = buffer1[3*idx1+1];
            buffer[3*idx+2] = buffer1[3*idx1+2];
        }
}

const char *Crop::FilterName()
{
    return "Crop";
}

/******************************************************/



void Transpose::Execute()
{
    int i, j;
    int height = input->GetHeight();
    int width = input->GetWidth();
    
    if(input == NULL)
    {
        char msg[1024];
        sprintf(msg, "%s: no input!\n", FilterName());
        DataFlowException e(FilterName(), msg);
        throw e;
    }
    
    output.ResetSize(height, width);
    
    
    for (int i = 0; i < height; i++){
        
        for (int j = 0; j < width; j++)
        {
            unsigned char red = (input->GetPixel(j, i)[0]);
            unsigned char green = (input->GetPixel(j, i)[1]);
            unsigned char blue =  (input->GetPixel(j, i)[2]);
            unsigned char pixel[] = {red, green, blue};
            output.SetPixel(i,j,pixel);
        }
    }
    
}

const char *Transpose::FilterName()
{
    return "Transpose";
}

/******************************************************/
void Invert::Execute()
{
    int i, j;
    int width = input->GetWidth();
    int height = input->GetHeight();
    unsigned char val = 255;
    
    if(input == NULL)
    {
        char msg[1024];
        sprintf(msg, "%s: no input!\n", FilterName());
        DataFlowException e(FilterName(), msg);
        throw e;
    }
    
    output.ResetSize(width, height);
    
    
    for(i = 0; i < width; i++)
    {
        for(j = 0; j < height; j++)
        {
            
            unsigned char red = (val-(input->GetPixel(i, j)[0]));
            unsigned char green = (val-(input->GetPixel(i, j)[1]));
            unsigned char blue =  (val- (input->GetPixel(i, j)[2]));
            unsigned char pixel[] = {red, green, blue};
            
            output.SetPixel(i, j, pixel);
        
        }
    }
}


const char *Invert::FilterName()
{
    return "Invert";
}

/******************************************************/

void Checkerboard::Execute()
{
    int i, j;

    
    if(input == NULL)
    {
        char msg[1024];
        sprintf(msg, "%s: no input!\n", FilterName());
        DataFlowException e(FilterName(), msg);
        throw e;
    }
    
    if(input2 == NULL)
    {
        char msg[1024];
        sprintf(msg, "%s: no input2!\n", FilterName());
        DataFlowException e(FilterName(), msg);
        throw e;
    }
    
    if((input->GetWidth()|input->GetHeight()) != (input2->GetWidth() | input2->GetHeight())){
        char msg[1024];
        sprintf(msg, "%s: Image sizes do not match!\n", FilterName());
        DataFlowException e(FilterName(), msg);
        throw e;
    }
    
    int width = input->GetWidth();
    int height = input->GetHeight();  //this is assuming both images are the same width and height
    
    
    output.ResetSize(width,height);
    

    for(i=0; i < width; i++){
        for(j=0; j< height; j++){
            if((i/10+j/10)%2==0){
                unsigned char *p = input->GetPixel(i,j);
                output.SetPixel(i, j, p);
            }
            else{
                unsigned char *p2 = input2->GetPixel(i,j);
                output.SetPixel(i, j, p2);
            }
            
        }
    }
}


const char *Checkerboard::FilterName()
{
    return "Checkerboard";
}

/******************************************************/


void Color::Execute()
{
    int i, j;
    
    output.ResetSize(width, height);
    
    for(i = 0; i < width; i++)
    {
        for(j = 0; j < height; j++)
        {
            output.Getdata()[3*(j*width+i)+0] = red;
            output.Getdata()[3*(j*width+i)+1] = green;
            output.Getdata()[3*(j*width+i)+2] = blue;
        }
    }
}

const char *Color::SourceName()
{
    return "SourceName";
}


/******************************************************/


void CheckSum::OutputCheckSum(const char *file)
{
    FILE* f = fopen(file, "w");
    
    int i, j;
    int width = input->GetWidth();
    int height = input->GetHeight();
    
    //automatically does modulo 256 when summing up the colors
    unsigned char red = 0;
    unsigned char green = 0;
    unsigned char blue = 0;
    
    if(input == NULL)
    {
        char msg[1024];
        sprintf(msg, "%s: no input!\n", SinkName());
        DataFlowException e(SinkName(), msg);
        throw e;
    }
    
    
    
    for(i = 0; i < width; i++)
    {
        for(j = 0; j < height; j++)
        {
            red += input->Getdata()[3*(j*width+i)+0];
            green += input->Getdata()[3*(j*width+i)+1];
            blue += input->Getdata()[3*(j*width+i)+2];
        }
    }
    
    fprintf(f, "CHECKSUM: %d, %d, %d\n", (int )red, (int)green, (int)blue);
    
    fclose(f);
}

const char *CheckSum::SinkName()
{
    return "CheckSum";
}



