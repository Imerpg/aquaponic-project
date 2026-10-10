#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main()
{
	int niveau = 0; //Définition du niveau
	int gpio = 4; //Définition de la GPIO 
	wiringPiSetup(); //Initialisation
	//Met la gpio en resistance pull_up
	pinMode(gpio, PUD_UP);

	//Lecture de la GPIO
	niveau = digitalRead(gpio);
	if(niveau == 1)
	{
		printf("Niveau trop bas\n");
	}
	else if(niveau == 0)
	{
		printf("Niveau correct\n");
	}
}
