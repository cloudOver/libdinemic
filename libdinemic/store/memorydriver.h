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

#ifndef MEMORYDRIVER_H
#define MEMORYDRIVER_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <libdinemic/dmodel.h>
#include <libdinemic/store/storeinterface.h>

class MemoryDriver : public StoreInterface
{
    friend class StoreInterface;
    friend class SyncInterface;

    // For test purposes
    friend class TestStoreObjectAdd;
    friend class TestVis;

    std::string last_update_id;
    DHeaders last_update;
    std::vector<std::string> chains;

protected:
    /// Main data store. List and dictionaries are implemented by syncinterface
    /// and dmodel. Lists and hashes are for helper purposes only.
    std::unordered_map<std::string, std::string> store;
    std::unordered_map<std::string, std::vector<std::string> > lists;
    std::unordered_map<std::string, DHeaders> updates;
    std::vector<std::string> processed_updates;
    std::vector<std::string> objects;

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
    MemoryDriver();

    std::vector<std::string> object_list(const std::string &filter);
    std::vector<std::string> chain_list();

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

//    void dict_set(NModel *model, const string &name, const string &key, const string &value);
//    string dict_get(NModel *model, const string &name, const string &key);
//    void dict_del(NModel *model, const string &name, const string &key);
//    vector<string> dict_keys(NModel *model, const string &name);
};

#endif // MEMORYDRIVER_H
