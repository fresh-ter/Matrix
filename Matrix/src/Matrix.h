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
    Matrix(int matrix_pinDigits[4], int matrix_pinSegments[8]);
    ~Matrix();

    void showMatrix(int number, int dot_point);
    void showIntNumber(int number);
protected:

private:
    void showNumber(int num,int dig);
    void m_showNumber(int number);

    int pinDigits[4];
    int pinSegments[8];

    byte m_numbers[10];

    int number;
    int number1;
    int number2;
};

#endif // MATRIX_H
