/**
Copyright (C) 2016-2018 cloudover.io ltd.
This file is part of the dinemic.io project

Licensee holding a valid commercial license for this software may use it in
accordance with the terms of the license agreement between cloudover.io ltd. and
the licensee.

Alternatively you may use this software under following terms of GNU Affero GPL
v3 license:

This program is free software: you can redistribute it and/or modify it under
the terms of the GNU Affero General Public License as published by the Free
Software Foundation, either version 3 of the License, or (at your option) any
later version. For details contact with the cloudover.io company:
https://cloudover.io/


This program is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE.  See the GNU Affero General Public License for more details.

You should have received a copy of the GNU Affero General Public License along
with this program.  If not, see <http://www.gnu.org/licenses/>.

By contributing to this project you agree to use your modifications and code
snippets under both licensing terms: GNU AGPL3 and commercial.
*/

#ifndef SYNCINTERFACE_H
#define SYNCINTERFACE_H

#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <fstream>
#include <thread>
#include <mutex>
#include <unordered_map>
#include <vector>
#include <libdinemic/daction.h>
#include <libdinemic/dheaders.h>
#include <libdinemic/utils.h>
#include <stdio.h>

#ifdef DINEMIC_BUILD
#include <boost/regex.hpp>
#include <boost/algorithm/string/replace.hpp>
#endif

#include <libdinemic/store/storeinterface.h>

#define SYNC_RETRANSMIT_LAST "last"
#define SYNC_PREVIOUS_NONE "none"

/// Minimum length of ID, which should be ignored. This should be less than length of "LAST"
#define SYNC_MIN_MSGID_LEN 4

class SyncInterface
{
    /// Map of model names. Each model is related to actions done on it (create,
    /// update, delete, etc.) and list of NAction objects which should be
    /// executed on event.
    std::unordered_map<std::string, std::vector<DAction *> > on_create_listeners;
    std::unordered_map<std::string, std::vector<DAction *> > on_created_listeners;
    std::unordered_map<std::string, std::vector<DAction *> > on_update_listeners;
    std::unordered_map<std::string, std::vector<DAction *> > on_updated_listeners;
    std::unordered_map<std::string, std::vector<DAction *> > on_delete_listeners;
    std::unordered_map<std::string, std::vector<DAction *> > on_deleted_listeners;
    std::unordered_map<std::string, std::vector<DAction *> > on_remove_listeners;
    std::unordered_map<std::string, std::vector<DAction *> > on_removed_listeners;

    std::string _wildcard_to_regex(const std::string &wildcard);
    std::string _regex_to_wildcard(const std::string &regex);

    /**
     * @brief _add_listener Add new listener to sync interface related to action
     * on the model
     * @param model_name Name of model related with this action. This could be a
     * exact field, i.e. Node:ID:address_list:1 or wildcard, i.e. Node:*
     * @param listeners Reference to listeners list, where new action should be
     * placed
     * @param action Pointer to the action
     */
    void _add_listener(const std::string &filter, std::unordered_map<std::string, std::vector<DAction *> > &listeners, DAction *action);
    void _remove_listener(const std::string &filter, std::unordered_map<std::string, std::vector<DAction *> > &listeners, DAction *action);
    std::unordered_map<std::string, std::vector<DAction *> > _get_listeners(const std::unordered_map<std::string, std::vector<DAction *> > &listeners, const std::string &filter="");

    std::vector<DAction *> _find_listeners(const std::string &field, DHeaders &headers, std::unordered_map<std::string, std::vector<DAction *> > &listeners);
    long queue_position;

    /// This function calls process_queue method in loop until agent_running is true.
    virtual void agent_thread();
    std::thread agent;
    std::mutex lock;

    /// Variables and thread used for debuging statistics
    long updates_processed;
    long updates_generated;
    long updates_rejected;

    std::thread updates_monitor;
    bool updates_monitor_running;
    /// If true, thread will print debug statistics
    bool updates_monitor_debug;
    void updates_monitor_thread();

protected:
    /// List of updates pending for processing
    std::vector<DHeaders> message_queue;

    virtual void _lock_queue();
    virtual void _unlock_queue();

    /// Agent loop is running until this is true
    bool agent_running;

    /// Notifies if all agents are started. USed by wait_running() method
    bool agent_started;
    StoreInterface *store;

    /**
     * Request missing message retransmission from other peers
     * @param message_id ID of message
     */
    virtual void request_retransmit(const std::string &message_id);

    /**
     * Use this method to store new messages in queue, received by agent
     * @param headers
     */
    virtual void store_message(DHeaders &headers);

    /**
     * Get stored update from StoreInterface. This method could be used by Sync
     * Drivers to go over friendship with StoreInterface.
     * @param update_id ID of update
     * @return DHeaders object with update's headers
     */
    DHeaders update_get(const std::string &update_id);

    /**
     * Check in StoreInterface if update was processed by this SyncInterface.
     * This method goes over firiendship limitations for Sync Drivers.
     * @param update_id ID of update
     * @return True if update was processed
     */
    bool update_processed(const std::string &update_id);

public:
    SyncInterface(StoreInterface *store);
    SyncInterface(const SyncInterface &copy);
    virtual ~SyncInterface();

    /**
     * Call this method to wait until all sync agents are running
     */
    virtual void wait_running();

    /**
     * This method should be used by models (exactly NModel) to notify other
     * nodes about changes in database. It signs update. In derived classes it should
     * send the notification across the network
     * @param object pointer to DModel object, which sends notification
     * @param headers All unsigned headers of notification
     * @return Signed object with headers. Original headers from pointer are
     * modified too.
     */
    virtual DHeaders &notify(DModel *object, DHeaders &headers);

    /**
     * Process messages stored in queue
     * @return Number of processed updates
     */
    int process_queue();

    /**
     * Manage actions on model which should be executed before new object
     * of this model is created anywhere in cluster. You can filter updates by
     * NAction's pattern parameter.
     * @param filter Filter updates to match this action
     * @param action Pointer to DAction
     */
    void add_on_create_listener(const std::string &filter, DAction *action);
    void remove_on_create_listener(const std::string &filter, DAction *action);
    const std::unordered_map<std::string, std::vector<DAction *> > get_on_create_listeners();

    /**
     * Manage actions on model which should be executed after new object
     * of this model is created anywhere in cluster. You can filter updates by
     * NAction's pattern parameter.
     * @param filter Filter updates to match this action
     * @param action Pointer to DAction
     */
    void add_on_created_listener(const std::string &filter, DAction *action);
    void remove_on_created_listener(const std::string &filter, DAction *action);
    const std::unordered_map<std::string, std::vector<DAction *> > get_on_created_listeners();

    /**
     * Manage actions on model which should be executed before any object
     * of this model is updated. You can filter updates by NAction's pattern
     * parameter.
     * @param filter Filter updates to match this action
     * @param action Pointer to DAction
     */
    void add_on_update_listener(const std::string &filter, DAction *action);
    void remove_on_update_listener(const std::string &filter, DAction *action);
    const std::unordered_map<std::string, std::vector<DAction *> > get_on_update_listeners();

    /**
     * Manage actions on model which should be executed after any object
     * of this model is updated. You can filter updates by NAction's pattern
     * parameter.
     * @param filter Filter updates to match this action
     * @param action Pointer to DAction
     */
    void add_on_updated_listener(const std::string &filter, DAction *action);
    void remove_on_updated_listener(const std::string &filter, DAction *action);
    const std::unordered_map<std::string, std::vector<DAction *> > get_on_updated_listeners();

    /**
     * Manage actions on model which should be executed before any field from
     * model's instance (object in database) is removed. You can filter events
     * by NAction's pattern parameter.
     * @param filter Filter updates to match this action
     * @param action Pointer to DAction
     */
    void add_on_delete_listener(const std::string &filter, DAction *action);
    void remove_on_delete_listener(const std::string &filter, DAction *action);
    const std::unordered_map<std::string, std::vector<DAction *> > get_on_delete_listeners();

    /**
     * Manage actions on model which should be executed after any field from
     * model's instance (object in database) is removed. You can filter events
     * by NAction's pattern parameter.
     * @param filter Filter updates to match this action
     * @param action Pointer to DAction
     */
    void add_on_deleted_listener(const std::string &filter, DAction *action);
    void remove_on_deleted_listener(const std::string &filter, DAction *action);
    const std::unordered_map<std::string, std::vector<DAction *> > get_on_deleted_listeners();

    /**
     * Manage actions on model which should be executed before model's instance
     * is removed from database. You can use filter events by NAction's pattern
     * parameter.
     * @param filter Filter updates to match this action
     * @param action Pointer to DAction
     */
    void add_on_remove_listener(const std::string &filter, DAction *action);
    void remove_on_remove_listener(const std::string &filter, DAction *action);
    const std::unordered_map<std::string, std::vector<DAction *> > get_on_remove_listeners();

    /**
     * Manage actions on model which should be executed after model's instance
     * is removed from database. You can use filter events by NAction's pattern
     * parameter.
     * @param filter Filter updates to match this action
     * @param action Pointer to DAction
     */
    void add_on_removed_listener(const std::string &filter, DAction *action);
    void remove_on_removed_listener(const std::string &filter, DAction *action);
    const std::unordered_map<std::string, std::vector<DAction *> > get_on_removed_listeners();

    /**
     * Start agent in background
     */
    virtual void start_agent();

    /**
     * Stop previously started agent
     */
    virtual void stop_agent();

    /**
      * Print Sync update statistics
      */
    void print_update_stats(bool show);
};

#endif // SYNCINTERFACE_H
