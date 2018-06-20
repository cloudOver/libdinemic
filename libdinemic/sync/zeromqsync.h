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

#ifndef ZEROMQSYNC_H
#define ZEROMQSYNC_H

#include <libdinemic/dmodel.h>
#include <libdinemic/sync/syncinterface.h>

#ifdef DINEMIC_BUILD
#include <zmq.h>
#include <poll.h>
#include <signal.h>
#include <unistd.h>
#include <signal.h>
#endif

#include <mutex>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>
#include <string.h>
#include <stdio.h>

struct ZeroMQPublisher {
    void *context;
    void *socket;
    std::string uri;
    bool inactive;
};

class ZeroMQSync : public SyncInterface
{
    void *publisher_context;
    void *publisher_socket;

    std::map<std::string, ZeroMQPublisher> publishers;

    std::thread zeromq_subscriber;
    std::thread zeromq_listener;
    std::thread zeromq_announce;

    bool zeromq_agent_running;

    pid_t avahi_service;

    std::mutex publisher_list_lock;
    void lock();
    void unlock();

    /**
     * Connect with all peers and read theirs messages
     */
    void zeromq_agent_subscriber();
    bool zeromq_agent_subscriber_started;

    /**
     * Listen for other agents in network
     */
    void zeromq_agent_listener();
    bool zeromq_agent_listener_started;

    /**
     * Announce this agent
     */
    void zeromq_agent_announce();
    bool zeromq_agent_announce_started;

    std::vector<std::string> get_peers();

    void request_retransmit(const std::string &message_id);

public:
    ZeroMQSync(StoreInterface *store);
    virtual ~ZeroMQSync();
    void wait_running();

    DHeaders &notify(DModel *object, DHeaders &headers);

    void start_agent();
    void stop_agent();
};

#endif // ZEROMQSYNC_H
