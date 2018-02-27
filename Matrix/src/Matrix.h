/*
  Matrix.h
  Created by Terminator, February 27, 2018.
*/
#ifndef MATRIX_H
#define MATRIX_H

#include <Arduino.h>

class Matrix
{
public:
    Matrix(int pind[4], int pins[8]);
    ~Matrix();

    void showMatrix(int number, int dot);
protected:

private:
    void showNumber(int num,int dig);

    int pinDigits[4];
    int pinPins[8];

    byte numbers[10];

    int number;
    int number1;
    int number2;
};

#endif // MATRIX_H
