#ifndef PERSON_H
#define PERSON_H

#include <libdinemic/dmodel.h>

class Person : public DModel
{
public:
    Person(const std::string &db_id, StoreInterface *store, SyncInterface *sync, DModel *parent=NULL);
    Person(DModel *parent);
    Person(StoreInterface *store,
           SyncInterface *sync,
           const std::vector<std::string> &authorized_keys);

    void set_name(std::string name);
    std::string get_name();

    void say(std::string phrase);
};

#endif // PERSON_H
