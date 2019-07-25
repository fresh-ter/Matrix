/*
  Matrix.h
  Created by Terminator, February 27, 2018.
*/
#include "Matrix.h"

Matrix::Matrix(char share_contact) {
	if(share_contact == 'C') {
		sign = false;
		negative_sign = true;
	}
	else if(share_contact == 'A') {
		sign = true;
		negative_sign = false;
	}

	m_arrayInitialization();

	millis_int = 0;
}

Matrix::~Matrix() {
	//dtor
}

void Matrix::setSegmentPins(int matrix_pinSegments[8]) {
	pinSegments[0] = matrix_pinSegments[0];
	pinSegments[1] = matrix_pinSegments[1];
	pinSegments[2] = matrix_pinSegments[2];
	pinSegments[3] = matrix_pinSegments[3];
	pinSegments[4] = matrix_pinSegments[4];
	pinSegments[5] = matrix_pinSegments[5];
	pinSegments[6] = matrix_pinSegments[6];
	pinSegments[7] = matrix_pinSegments[7];

	//dig = true;
}

void Matrix::setDigitPins(int *matrix_pinDigits, int matrix_sizeDigits) {
	sizeDigits = matrix_sizeDigits;

	int b[sizeDigits];

	for(int c=0,c1=sizeDigits-1; c<sizeDigits; c++,c1--)
    {
        b[c] = *(matrix_pinDigits+c1);
    }
    pinDigits = &b[0];

	m_reset();
}

void Matrix::m_arrayInitialization() {
	m_digits[0] = B11111100; // 0
	m_digits[1] = B01100000; // 1
	m_digits[2] = B11011010; // 2
	m_digits[3] = B11110010; // 3
	m_digits[4] = B01100110; // 4
	m_digits[5] = B10110110; // 5
	m_digits[6] = B10111110; // 6
	m_digits[7] = B11100000; // 7
	m_digits[8] = B11111110; // 8
	m_digits[9] = B11110110; // 9

	m_chars[4] = B10011110; // E
	m_chars[17] = B00001010; // r
	m_chars[26] = B00000000; // (Space)
	m_chars[27] = B00000010; // -

	m_error[3] = B10011110; // E
	m_error[2] = B00001010; // r
	m_error[1] = B00001010; // r
	m_error[0] = B00000000; // (Space)
}

void Matrix::m_reset() {
	for(int i=0; i<8; i++)
		pinMode(pinSegments[i],OUTPUT);
	for(int i=0; i<sizeDigits; i++) {
		pinMode(*(pinDigits+i),OUTPUT);
		digitalWrite(*(pinDigits+i),negative_sign);
	}
}

int Matrix::m_pow(int i, int n) { 
	int i_r=i;
	for(int c=1; c<n; c++)
		i_r=i_r*i;

	return i_r;
}

void Matrix::showIntNumber(int number) {
	if(number < m_pow(10, sizeDigits) && number >= 0) {
		number1=number;

		for(int i=0; i<sizeDigits; i++) {
			number2=number1%10;
			number1=number1/10;

			m_showDigit(number2);

			for(int j=0; j<sizeDigits; j++)
				digitalWrite(*(pinDigits+j),negative_sign);
			digitalWrite(*(pinDigits+i),sign);

			delay(1);
			m_reset();
		}
	}
	else if(number < 0 && number > (-(m_pow(10, sizeDigits-1))) 
			&& sizeDigits > 1) {
		number = number * (-1);
		number1=number;

		for(int i=0; i<(sizeDigits-1); i++) {
			number2=number1%10;
			number1=number1/10;

			m_showDigit(number2);

			for(int j=0; j<sizeDigits; j++)
				digitalWrite(*(pinDigits+j),negative_sign);
			digitalWrite(*(pinDigits+i),sign);

			delay(1);

			m_reset();
		}

		m_showChar('-');

		for(int j=0; j<sizeDigits; j++)
			digitalWrite(*(pinDigits+j),negative_sign);
		digitalWrite(*(pinDigits+(sizeDigits-1)),sign);

		delay(1);

		m_reset();
	}
	else {
		if(millis()-millis_int <= 300) {
		m_showError();
		m_reset();
		}

		if(millis()-millis_int >= 300*2) {
			m_reset();

			millis_int = millis();
		}
	}
}

void Matrix::showError() {
	if(millis()-millis_int <= 1000) {
		m_showError();
		m_reset();
		}

		if(millis()-millis_int >= 1000*2) {
			m_reset();

			millis_int = millis();
		}
}

// void Matrix::showNumber(int num, int dig) {
// 	for(int i=0; i<8; i++)
// 	{
// 		if(bitRead(m_numbers[num], 7-i) == HIGH)
// 			digitalWrite(pinSegments[i], HIGH);
// 		else
// 			digitalWrite(pinSegments[i], LOW);
// 	}
// 	if(dig==1)
// 		digitalWrite(pinSegments[7], HIGH);
// }

void Matrix::m_showError() {
	if(sizeDigits >= 3)
	{
		for(int i1=3; i1>0; i1--) {
			for(int i=0; i<8; i++) {
				if(bitRead(m_error[i1], 7-i) == HIGH)
					digitalWrite(pinSegments[i], HIGH);
				else
					digitalWrite(pinSegments[i], LOW);
			}

			for(int j=0; j<sizeDigits; j++)
				digitalWrite(*(pinDigits+j),negative_sign);
			digitalWrite(*(pinDigits+(i1-1)),sign);

			delay(1);
			}
		m_reset();
	}
	else
	{
		for(int i=0; i<8; i++) {
			if(bitRead(m_error[3], 7-i) == HIGH)
				digitalWrite(pinSegments[i], HIGH);
			else
				digitalWrite(pinSegments[i], LOW);
		}

		for(int j=0; j<sizeDigits; j++)
			digitalWrite(*(pinDigits+j),negative_sign);
		digitalWrite(*(pinDigits+(sizeDigits-1)),sign);

		delay(1);
		m_reset();
	}
}

void Matrix::m_showDigit(int digit) {
	for(int i=0; i<8; i++)
	{
		if(bitRead(m_digits[digit], 7-i) == HIGH)
			digitalWrite(pinSegments[i], HIGH);
		else
			digitalWrite(pinSegments[i], LOW);
	}
}


void Matrix::m_showChar(char c) {
	int number = 26;
	switch(c) {
		case 'a':
			number = 0;
			break;
		case 'b':
			number = 1;
			break;
		case 'c':
			number = 2;
			break;
		case 'd':
			number = 3;
			break;
		case 'e':
			number = 4;
			break;
		case 'f':
			number = 5;
			break;
		case 'g':
			number = 6;
			break;
		case 'h':
			number = 7;
			break;
		case 'i':
			number = 8;
			break;
		case 'j':
			number = 9;
			break;
		case 'k':
			number = 10;
			break;
		case 'l':
			number = 11;
			break;
		case 'm':
			number = 12;
			break;
		case 'n':
			number = 13;
			break;
		case 'o':
			number = 14;
			break;
		case 'p':
			number = 15;
			break;
		case 'q':
			number = 16;
			break;
		case 'r':
			number = 17;
			break;
		case 's':
			number = 18;
			break;
		case 't':
			number = 19;
			break;
		case 'u':
			number = 20;
			break;
		case 'v':
			number = 21;
			break;
		case 'w':
			number = 22;
			break;
		case 'x':
			number = 23;
			break;
		case 'y':
			number = 24;
			break;
		case 'z':
			number = 25;
			break;
		case ' ':
			number = 26;
			break;
		case '-':
			number = 27;
			break;
	}

	for(int i=0; i<8; i++)
	{
		if(bitRead(m_chars[number], 7-i) == HIGH)
			digitalWrite(pinSegments[i], HIGH);
		else
			digitalWrite(pinSegments[i], LOW);
	}
}
