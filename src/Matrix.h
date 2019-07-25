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
	//Matrix(	int matrix_pinDigits[4], int matrix_pinSegments[8],
	//		char share_contact);

	Matrix(char share_contact);
	~Matrix();

	// void setSegmentPins(int matrix_pinSegments[7]);
	void setSegmentPins(int matrix_pinSegments[8]);
	void setDigitPins(int *matrix_pinDigits, int matrix_sizeDigits);

	// void showMatrix(int number, int dot_point);
	void showIntNumber(int number);

	void showError();
protected:

private:
	void m_arrayInitialization();
	void m_showDigit(int digit);
	void m_showChar(char c);

	void m_showError();

	void m_reset();
	int m_pow(int i, int n);

	// void showNumber(int num,int dig);

	bool sign;
	bool negative_sign;

	//bool dig;

	byte m_error[4];

	unsigned long millis_int;

	int sizeDigits;
	int *pinDigits;
	int pinSegments[8];

	byte m_digits[10];
	byte m_chars[28];

	int number;
	int number1;
	int number2;
};

#endif // MATRIX_H
