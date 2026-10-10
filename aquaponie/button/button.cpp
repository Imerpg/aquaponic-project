#include <wiringPi.h>
#include <iostream>

using namespace std;

int main(int argc, char const *argv[])
{
    int res = 0;
    int gpio = 4;
    wiringPiSetup();
    pinMode(gpio, PUD_UP);

    int bouton = 0;

    while (1)
    {
        bouton = digitalRead(gpio);
        // Change de page
        if (bouton == 1)
        {
            res++;
        }

        // Si il arrive a 3 (pge 2)
        if(res >= 3) {
            res = 0;
        }
        return res;
    }
    
    return 0;
}


