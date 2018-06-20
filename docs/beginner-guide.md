Key-value store
===============

Each object in Libdinemic database (whatever is behind this API) is stored as the
set of key-value pairs. For example, database model Person and each its object
consisting of fields:
 - first_name
 - last_name
 - date_of_birth

will create four entries in database. Three of them will be related to above
data. Fourth field will contain information about objects authorized to update
certain object. This field is called authorized_kyes and has form of list. It
means, that each authorized key will be a separate entry too. With two
authorized objects, following entries in database will be made:
  - Person:ID:value_first_name
  - Person:ID:value_last_name
  - Person:ID:value_date_of_birth
  - Person:ID:list_authorized_keys:value_uw8f98q4da0
  - Person:ID:list_authorized_keys:value_fwerp9q4pcw


Accessing store through Libdinemic API
--------------------------------
To create new object use following (assume, that store and sync drivers were
created previously):
```C++
DModel person("Person", store, sync, vector<string>());
```
Above example will create new, empty object with one authorized key. Also new
key pair will be created in local key store (GPG). Public key will be appended
to the authorized_keys list in this model. To set fields with this model, use
following code:
```C++
person.set("first_name", "John");
person.set("last_name", "Travolta");
person.set("date_of_birth", "1970-01-01 01:01");
```

Mention, that your updates will be processed by store. It could take some time
to update it. This is related to update-chain processing. If any pending
updates are present in queue, those updates should be executed first, before
yours. If you need to use field immediately after updating it, use NAction
instead.

To store data in form of list, use following code:
```C++
#include <libdinemic/dmodel.h>

...

person.list_append("albums", "unknown album 1");
person.list_append("albums", "unknown album 2");
person.list_set("albums", 0, "hey joe!");
```

In final version of Libdinemic library, all updates should appear on all nodes in
network. Field names could contain only letters and numbers (a-z, A-Z, 0-9).
All data stored in updates is stored in base64 format. It is not defined how
database stores data internally.

All single fields (created by set and accessible by get) have prefix value_ in
database fields (thus, in updates too). All lists have prefix list_, as in
example, i.e.:
``` list_authorized_keys ```
To iterate over list's items, new singular fields are created with whole list
prefix.

Using NAction for models
========================
One of principles of Libdinemic library is to allow Event Driven Development. To
react on database updates (i.e. for certain field), modify following example:
```C++
#include <libdinemic/daction.h>

...

class MyListener: public DAction {
    void on_update(DModel *parent, const DActionFlags &flags, DHeaders &headers, const string &key, const string &old_value, const string &new_value) {
        if (flags.is_verified()) {
            cout << "We can trust this update - it is verified by public key!" << endl;
        } else {
            cout << "Update was not verified by object's public key :(" << endl;
        }
    }

    void on_updated(DModel *parent, const DActionFlags &flags, DHeaders &headers, const string &key, const string &old_value, const string &new_value) {
        cout << "Model was updated!" << endl;
    }
};

MyListener listener;

sync->add_on_create_listener("Person:*", &listener);
```

Remember, that Libdinemic is not storing object instances internally. Each time the
method on NAction is called (create, created, update, updated, remove, delete,
deleted), NObject instance is recreated from scratch by Libdinemic. You can access
object's data only by Libdinemic api. To access object use object pointed by *parent
parameter. This is an instance of your object.

Above example calls NAction listener on each Person update. To narrow this
behavior, you can use pattern in registering listener:
```C++
sync->add_on_create_listener("Person:*:list_albums:*", &listener);
```

Application skeleton
====================
This is not final design yet.

To easily run application, without handling store, sync and other stuff related
to Libdinemic's startup, you can use NApp skeleton to build your own application.

Let's create new class based on NApp:
```C++
#include <libdinemic/dapp.h>

...

class MyApp : public DApp
{
    ...

public:
    MyApp(int argc, char **argv);
    void create();
    void launch();
    void remove();
};
```

In create method you should contain all operations necessary to be launched
when new instance of application in your cluster will be created (i.e. new node
is created. Especially You should create there new models (thus new key pairs
will be created too!). The launch method will be used each time your
application is re-created in cluster (i.e. node is starting). Here you should
define all NAction listeners, update models and so on. Another method is stop
which is called by NApp on application shutdown. The remove method is called
to remove all application-related stuff from database. It means you should
clean up the database.

So, create proper methods in .cpp file. Then, in main() put following code:
```C++
int main(int argc, char **argv) {
    MyApp app(argc, argv);
    app.exec();
    return 0;
}
```

Then launch your application with one of following parameters:
* create
* launch
* stop
* remove

Above parameters are related to NApp methods. Remember to prepare proper
configuration file in directory with your application.

Database migrations
===================
Libdinemic API is created to base on Key-Value stores, like Redis, Memcached or just
memory stores. There is no need to provide migrations known from SQL databases,
where data was stored in fixed tables. K-V stores give you flexibility in data
organization. If in your App cluster are old and new versions of application,
then proper fields in updated objects should be created automatically. Just
remember to provive everywhere default values in get methods on NModels.
