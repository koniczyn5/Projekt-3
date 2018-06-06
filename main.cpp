#include<iostream>
#include"szkola.h"
#include"lista.h"
#include"interfejs.cpp"

using namespace std;

int main()
{
	//Wersja 1.0
	lista<klasa> klasy;
	lista<sala> sale;
	lista<pracownik> pracownicy;
	lista<nauczyciel> nauczyciele;
	lista<wychowawca> wychowawcy;
	lista<planLekcji> plany;
	lista<uczen> uczniowie;
	MENU(cin, cout, klasy, sale, uczniowie, pracownicy, nauczyciele, wychowawcy, plany);
	return 0;
}
