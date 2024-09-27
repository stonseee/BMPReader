#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<Windows.h>
#include<iostream>
#include<fstream>
#include<string>
#include<conio.h>
#include<map>

using std::cin;
using std::cout;
using std::endl;

class BMPReader
{
private:
    BITMAPFILEHEADER header;
    BITMAPINFOHEADER infoHeader;
    RGBQUAD** rgb;
    std::string fileName;
public:
    BMPReader()
    {
        //cout << "BMPReader constructor " << this << endl;
    }
    ~BMPReader()
    {
        //cout << "BMPReader destructor  " << this << endl;        
    }

    void load(const std::string& fileName);
    void info();
    void display();
    void open();
    void clear();
    bool empty();

    int ascii_comparison(char sym);
    int sum_by_binary(int a, int b);
    int sum_by_binary(int a, int b, int c, int d);
};