#include "chatlistener.h"

ChatListener::ChatListener()
{

}

void ChatListener::apply(SyncInterface *sync, const std::string &filter) {
    sync->add_on_create_listener("Person:*", this);
    sync->add_on_update_listener("Person:*:value_phrase", this);
    sync->add_on_update_listener("Person:*:value_name", this);
}

void ChatListener::revoke(SyncInterface *sync, const std::string &filter) {
    sync->remove_on_create_listener("Person:*", this);
    sync->remove_on_update_listener("Person:*:value_phrase", this);
    sync->remove_on_update_listener("Person:*:value_name", this);
}

void ChatListener::on_create(DActionContext &context, const std::string &key) {
    std::cout << "New person was created: " << context.get_object().get_db_id() << std::endl;
}

void ChatListener::on_update(DActionContext &context, const std::string &key, const std::string &old_value, const std::string &new_value) {
    if (!context.is_verified()) {
        throw DFieldVerificationFailed("Update is not verified");
    }

    // Recreate person object. We will recreate it from ID stored in context
    Person person(context.get_object().get_db_id(), context.get_object().get_store_interface(), context.get_object().get_sync_interface());

    // Check if field, which was updated is called phrase. The same could be achieved by filter
    if (key == "value_phrase") {
        std::cout << person.get_name() << " says: " << new_value << std::endl;
    }
}
