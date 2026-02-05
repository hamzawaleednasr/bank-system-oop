#include "login.h"

int main()
{

	while (true && !lock)
		loginScreen::showLoginScreen();

	return 0;
}