#include <stdio.h>
#include "Core_System.h"
#include "UI.h"

int main(int argc, char const* argv[])
{
	initializeSystem(argc, argv);
	ShowWelcomeUI();
	system("pause");
}