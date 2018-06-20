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

#ifndef REDISSYNC_H
#define REDISSYNC_H

#include <fstream>
#include <iostream>
#include <utils.h>
#include <dmodel.h>
#include <sync/syncinterface.h>
#include <sys/time.h>

#ifdef DINEMIC_BUILD
#include <hiredis/hiredis.h>
#include <hiredis/async.h>

#ifdef __APPLE__
#include <hiredis/adapters/macosx.h>
#endif
#include <hiredis/adapters/libevent.h>
#endif

class RedisSync : public SyncInterface
{
    redisContext *redisCtx;
    redisAsyncContext *redisAsyncCtx;
    struct event_base *base;

    redisReply *reply;
    std::string hostname;
    int port;
    struct timeval timeout = { 1, 500000 };

    std::thread redis_agent;
    bool redis_agent_running;
    void redis_agent_run();

    friend void onMessage(redisAsyncContext *c, void *reply, void *privdata);
public:
    RedisSync(StoreInterface *store);
    virtual ~RedisSync();
    DHeaders &notify(DModel *object, DHeaders &headers);

    void start_agent();
    void stop_agent();
};

#endif // REDISSYNC_H
