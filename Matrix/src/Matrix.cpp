/*
  Matrix.h
  Created by Terminator, February 27, 2018.
*/
#include "Matrix.h"

Matrix::Matrix(int matrix_pinDigits[4], int matrix_pinSegments[8]) {
	//numbers = { B11111100, B01100000, B11011010,
				   //   B11110010, B01100110, B10110110,
				   //   B10111110, B11100000, B11111110,
				   //   B11110110
				   // };
	m_numbers[0] = B11111100; // 0
	m_numbers[1] = B01100000; // 1
	m_numbers[2] = B11011010; // 2
	m_numbers[3] = B11110010; // 3
	m_numbers[4] = B01100110; // 4
	m_numbers[5] = B10110110; // 5
	m_numbers[6] = B10111110; // 6
	m_numbers[7] = B11100000; // 7
	m_numbers[8] = B11111110; // 8
	m_numbers[9] = B11110110; // 9

	pinSegments[0] = matrix_pinSegments[0];
	pinSegments[1] = matrix_pinSegments[1];
	pinSegments[2] = matrix_pinSegments[2];
	pinSegments[3] = matrix_pinSegments[3];
	pinSegments[4] = matrix_pinSegments[4];
	pinSegments[5] = matrix_pinSegments[5];
	pinSegments[6] = matrix_pinSegments[6];
	pinSegments[7] = matrix_pinSegments[7];
	pinDigits[0] = matrix_pinDigits[3];
	pinDigits[1] = matrix_pinDigits[2];
	pinDigits[2] = matrix_pinDigits[1];
	pinDigits[3] = matrix_pinDigits[0];

	for(int i=0; i<8; i++)
		pinMode(pinSegments[i],OUTPUT);
	for(int i=0; i<4; i++) {
		pinMode(pinDigits[i],OUTPUT);
		digitalWrite(pinDigits[i],HIGH);
	}
}

Matrix::~Matrix() {
	//dtor
}

void Matrix::showMatrix(int number, int dot_point) {
	number1=number;

	for(int i=0; i<4; i++)
	{
		number2=number1%10;
		number1=number1/10;

		if(5-dot_point == i+1)
			showNumber(number2,1);
		else
			showNumber(number2,0);

		for(int j=0; j<4; j++)
			digitalWrite(pinDigits[j],HIGH);
		digitalWrite(pinDigits[i],LOW);

		delay(1);
	}
}

void Matrix::showIntNumber(int number) {
	number1=number;

	for(int i=0; i<4; i++)
	{
		number2=number1%10;
		number1=number1/10;

		m_showNumber(number2);

		for(int j=0; j<4; j++)
			digitalWrite(pinDigits[j],HIGH);
		digitalWrite(pinDigits[i],LOW);

		delay(1);
	}
}

void Matrix::showNumber(int num, int dig) {
	for(int i=0; i<8; i++)
	{
		if(bitRead(m_numbers[num], 7-i) == HIGH)
			digitalWrite(pinSegments[i], HIGH);
		else
			digitalWrite(pinSegments[i], LOW);
	}
	if(dig==1)
		digitalWrite(pinSegments[7], HIGH);
}

void Matrix::m_showNumber(int number) {
	for(int i=0; i<8; i++)
	{
		if(bitRead(m_numbers[number], 7-i) == HIGH)
			digitalWrite(pinSegments[i], HIGH);
		else
			digitalWrite(pinSegments[i], LOW);
	}
}
