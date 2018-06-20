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

#ifndef REDISDRIVER_H
#define REDISDRIVER_H

#include <string>
#include <vector>

#ifdef DINEMIC_BUILD
#include <hiredis/hiredis.h>
#endif

#include <libdinemic/dmodel.h>
#include <libdinemic/store/storeinterface.h>

/**
 * DANGER: This version is vulnerable for injections!
 */
class RedisDriver: public StoreInterface
{
    friend class StoreInterface;
    friend class SyncInterface;

    // For test purposes
    friend class TestStoreObjectAdd;
    friend class TestVis;

    std::string host;
    int port;
    int db_index;

    void *connect();
    void disconnect(void *c);

protected:
    void object_add(const std::string &id);

    void update_add(const DHeaders &update);
    DHeaders update_get(const std::string &update_id);
    std::string update_hash(const std::string &update_id);
    bool update_is_processed(const std::string &update_id);
    void update_mark_processed(const std::string &update_id);
    void update_set_last(const DHeaders &update);
    std::vector<DHeaders> update_get_list();

    std::string update_get_last_id();
    DHeaders update_get_last();

    void chain_add(const std::string &update_id);

public:
    RedisDriver();

    std::vector<std::string> object_list(const std::string &filter);

    std::vector<std::string> dump_keys();
    std::unordered_map<std::string, std::vector<std::string> > dump_lists();

    std::string get(DModel *model, const std::string &key, const std::string &def);
    void set(DModel *model, const std::string &key, const std::string &value);
    void del(DModel *model, const std::string &key);
    std::vector<std::string> keys(DModel *model, const std::string &pattern="*");

    void list_insert(DModel *model, const std::string &name, long index, const std::string &value);
    void list_append(DModel *model, const std::string &name, const std::string &value);
    std::string list_at(DModel *model, const std::string &name, long index);
    long list_length(DModel *model, const std::string &name);
    void list_delete(DModel *model, const std::string &name, long index);
    virtual long list_index(DModel *model, const std::string &name, const std::string &value);
    virtual void list_set(DModel *model, const std::string &name, long index, const std::string &value);

};

#endif // REDISDRIVER_H
