#include <iostream>
#include "BaseWindow.h"


int main()
{
    sf::err().rdbuf(NULL);
    BaseWindow::getInstance()->Run();

}
