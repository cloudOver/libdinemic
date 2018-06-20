#ifndef CHARGERSYNC_H
#define CHARGERSYNC_H
/*
#include <libdinemic/sync/syncinterface.h>
#include <string>
#include <curl/curl.h>
#include <time.h>
#include <libdinemic/dconfig.h>
#include <libdinemic/dheaders.h>

static size_t store_response(void *ptr, size_t size, size_t nmemb, void *data);

class ChargerSync : public SyncInterface
{
    CURL *curl;
    thread charger_agent;
    bool charger_agent_running;
    void charger_agent_run();

    string publish_url;
    string subscribe_url;

    string last_notification;
    void set_last_notification(string id);
    friend size_t store_response(void *ptr, size_t size, size_t nmemb, void *data);

public:
    ChargerSync(StoreInterface *store);
    ChargerSync(const ChargerSync &copy);
    ~ChargerSync();
    DHeaders &notify(DModel *object, DHeaders &headers);

    void start_agent();
    void stop_agent();
};
*/
#endif // CHARGERSYNC_H
