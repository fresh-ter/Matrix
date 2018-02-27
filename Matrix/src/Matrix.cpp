/*
  Matrix.h
  Created by Terminator, February 27, 2018.
*/
#include "Matrix.h"

Matrix::Matrix(int pind[4], int pins[8])
{
    //numbers = { B11111100, B01100000, B11011010,
                   //   B11110010, B01100110, B10110110,
                   //   B10111110, B11100000, B11111110,
                   //   B11110110
                   // };
    numbers[0] = B11111100; // 0
    numbers[1] = B01100000; // 1
    numbers[2] = B11011010; // 2
    numbers[3] = B11110010; // 3
    numbers[4] = B01100110; // 4
    numbers[5] = B10110110; // 5
    numbers[6] = B10111110; // 6
    numbers[7] = B11100000; // 7
    numbers[8] = B11111110; // 8
    numbers[9] = B11110110; // 9

    pinPins[0] = pins[0];
    pinPins[1] = pins[1];
    pinPins[2] = pins[2];
    pinPins[3] = pins[3];
    pinPins[4] = pins[4];
    pinPins[5] = pins[5];
    pinPins[6] = pins[6];
    pinPins[7] = pins[7];
    pinDigits[0] = pind[0];
    pinDigits[1] = pind[1];
    pinDigits[2] = pind[2];
    pinDigits[3] = pind[3];

    for(int i=0; i<8; i++)
        pinMode(pinPins[i],OUTPUT);
    for(int i=0; i<4; i++)
    {
        pinMode(pinDigits[i],OUTPUT);
        digitalWrite(pinDigits[i],HIGH);
    }
}

Matrix::~Matrix()
{
    //dtor
}

void Matrix::showMatrix(int number, int dot)
{
    number1=number;

    for(int i=0; i<4; i++)
    {
        number2=number1%10;
        number1=number1/10;

        if(dot == i+1)
            showNumber(number2,1);
        else
            showNumber(number2,0);

        for(int j=0; j<4; j++)
            digitalWrite(pinDigits[j],HIGH);
        digitalWrite(pinDigits[i],LOW);

        delay(1);
    }
}

void Matrix::showNumber(int num,int dig)
{
    for(int i=0; i<8; i++)
    {
        if(bitRead(numbers[num],7-i)==HIGH)
            digitalWrite(pinPins[i],HIGH);
        else
            digitalWrite(pinPins[i],LOW);
    }
    if(dig==1)
        digitalWrite(pinPins[7],HIGH);
}
