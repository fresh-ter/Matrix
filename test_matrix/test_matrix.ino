#include <Matrix.h>

int pinDigits[4] = {2,12,11,8};
int pinPins[8] = {9,13,4,6,7,10,3,5};
Matrix m(pinDigits,pinPins);

void setup()
{

}
void loop()
{
    m.showMatrix(1024,0);
}
