#include <iostream>
#include "chat.h"
using namespace std;

int main(int argc, char *argv[])
{
    Chat app(argc, argv);
    return app.exec();
}
