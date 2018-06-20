#ifndef CHAT_H
#define CHAT_H

#include <iostream>
#include <libdinemic/dapp.h>
#include "person.h"
#include "chatlistener.h"


class Chat : public DApp
{
    ChatListener listerer;
public:
    Chat(int argc, char **argv);
    void create();
    void oneshot();
};

#endif // CHAT_H
