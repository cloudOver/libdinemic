#include "person.h"

using namespace std;

Person::Person(const string &db_id, StoreInterface *store, SyncInterface *sync, DModel *parent)
    : DModel(db_id, store, sync, parent)
{
    // This constructor is used to recreate Person object in "send" mode, to
    // send new message
}

Person::Person(DModel *parent)
    : DModel("Person", parent)
{
    // This constructor could be used to create child objects. We don't want to
    // use it in this example
}

Person::Person(StoreInterface *store, SyncInterface *sync, const std::vector<string> &authorized_keys)
    : DModel("Person", store, sync, authorized_keys)
{
    // Only this constructor is used to create new objects directly in this
    // application
    set("name", "New Born");
}

void Person::set_name(string name) {
    set("name", name);
}

string Person::get_name() {
    return get("name");
}

void Person::say(string phrase) {
    set("phrase", phrase);
}
