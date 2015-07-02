/*
 image.h
 Brandon Cao

 
 */

#ifndef IMAGE_H
#define IMAGE_H

class Source;

class Image
{
public:
    Image(void); // Default constructor
    Image(int w, int h);//parameter constructer
    Image(Image &i);//copy constructer
    ~Image(); //deconstructer
    
    
    void ResetSize(int w, int h);
    int GetWidth() const; // returns width
    int GetHeight()const; // returns height
    unsigned char *Getdata() const{ return data; }//returns data
    unsigned char *GetPixel(int w, int h)const; // gets pixel
    void SetPixel(int w, int h, unsigned char *); // set pixel to whatever color or height or width
    void Update()const;
    void SetSource(Source *source);
    Source *src;
    



private:
    int w, h;
    unsigned char *data; // buffer for pixel

    
    
    
    
};


#endif
