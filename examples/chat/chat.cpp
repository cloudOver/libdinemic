#include "chat.h"

using namespace std;

Chat::Chat(int argc, char **argv)
    : DApp(argc, argv, "Chat", "Simple example of using Dinemic Framework. Launch in create mode to create your new identity in network. Launch in oneshot mode to send messages. Launch in launch mode to listen for others messages.")
{
    add_option("n", "name", "Your name in chat", false, DAppOptionMode_create);
    add_option("i", "id", "Identifier of person, which sends messages to chat board");
    add_option("m", "message", "Send message", false, DAppOptionMode_oneshot);

    listerer.apply(sync);
}

void Chat::create() {
    if (!has_option("name")) {
        cout << "Missing name parameter!" << endl;
        return;
    }

    Person person(store, sync, vector<string>());
    person.set_name(get_option("name").values[0]);
    cout << "Your new ID: " << person.get_db_id() << endl;
}

void Chat::oneshot() {
    if (!has_option("message") || !has_option("id")) {
        cout << "Missing message or id parameter!" << endl;
    }

    Person person(get_option("id").values[0], store, sync);
    person.say(get_option("message").values[0]);
}

