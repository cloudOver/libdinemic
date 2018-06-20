#ifndef CHATLISTENER_H
#define CHATLISTENER_H

#include <libdinemic/dmodel.h>
#include <libdinemic/daction.h>
#include <libdinemic/dexception.h>
#include <libdinemic/sync/syncinterface.h>
#include "person.h"

class ChatListener : public DAction
{
public:
    ChatListener();

    void apply(SyncInterface *sync, const std::string &filter="");
    void revoke(SyncInterface *sync, const std::string &filter="");

    void on_create(DActionContext &context, const std::string &key);
    void on_update(DActionContext &context,
                   const std::string &key,
                   const std::string &old_value,
                   const std::string &new_value);
};

#endif // CHATLISTENER_H
