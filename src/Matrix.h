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

	void showError();
protected:

private:
	void showNumber(int num,int dig);

	void m_showError();

	void m_showNumber(int number);
	void m_showChar(char c);

	void m_reset();

	byte m_error[4];

	unsigned long millis_int;

	int pinDigits[4];
	int pinSegments[8];

	byte m_numbers[10];
	byte m_chars[28];

	int number;
	int number1;
	int number2;
};

#endif // MATRIX_H
