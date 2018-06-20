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

#ifndef STOREINTERFACE_H
#define STOREINTERFACE_H

#include <vector>
#include <string>
#include <unordered_map>
#include <libdinemic/utils.h>

class DModel;

class StoreInterface
{
    friend class StoreInterface;
    friend class SyncInterface;

    // For test purposes
#ifndef DINEMIC_BUILD
    friend class TestStoreObjectAdd;
    friend class TestVis;
    friend int main(int, char **);
#endif

protected:
    /// Add new ID of stored object (used ony by StoreInterface)
    virtual void object_add(const std::string &id) = 0;

    /// Store new update in StoreInterface
    virtual void update_add(const DHeaders &update) = 0;

    /// Get stored update from StoreInterface
    virtual DHeaders update_get(const std::string &update_id) = 0;

    /// Get hash of update
    virtual std::string update_hash(const std::string &update_id) = 0;

    /// Check if update was processed
    virtual bool update_is_processed(const std::string &update_id) = 0;

    /// Mark update as processed
    virtual void update_mark_processed(const std::string &update_id) = 0;

    /// Set last known update of all chains
    virtual void update_set_last(const DHeaders &update) = 0;

    /// Add new chain of updates. To read all known chains, use chain_list. You
    /// can obtain list of all chains in database. This method should be used
    /// only by Sync drivers
    virtual void chain_add(const std::string &update_id) = 0;

public:
    StoreInterface();
    virtual ~StoreInterface();

    /// Get all keys in store (for debug purposes)
    virtual std::vector<std::string> dump_keys();

    /// Get list of IDs of all objects created in this StoreInterface.
    /// TODO: Implement filters
    virtual std::vector<std::string> object_list(const std::string &filter="");

    /// Get list of all chains - list update IDs, which has no previous
    virtual std::vector<std::string> chain_list();

    /// Get last known id of update in any chain
    virtual std::string update_get_last_id() = 0;

    /// Get last known update
    virtual DHeaders update_get_last() = 0;

    /// Get all updates from store. This could return large vector
    /// Use only for debug and tests
    virtual std::vector<DHeaders> update_get_list() = 0;

    /// Get all lists in store (for debug purposes)
    virtual std::unordered_map<std::string, std::vector<std::string> > dump_lists();

    /// Get element from store
    virtual std::string get(DModel *model, const std::string &key, const std::string &def);

    /// Set element in store
    virtual void set(DModel *model, const std::string &key, const std::string &value);

    /// Get all keys from store
    virtual std::vector<std::string> keys(DModel *model, const std::string &pattern="*");

    /// Delete element from store
    virtual void del(DModel *model, const std::string &key);

    /// Insert element to the list
    virtual void list_insert(DModel *model, const std::string &name, long index, const std::string &value);

    /// Append element at the end of list
    virtual void list_append(DModel *model, const std::string &name, const std::string &value);

    /// Get element at index
    virtual std::string list_at(DModel *model, const std::string &name, long index);

    /// Get position of element in list
    virtual long list_index(DModel *model, const std::string &name, const std::string &value);

    /// Update list at position
    virtual void list_set(DModel *model, const std::string &name, const long index, const std::string &value);

    /// Get list size
    virtual long list_length(DModel *model, const std::string &name);

    /// Delete element
    virtual void list_delete(DModel *model, const std::string &name, long index);

    /*virtual string dict_get(NModel *model, const string &name, const string &key);
    virtual void dict_set(NModel *model, const string &name, const string &key, const string &value);
    virtual void dict_del(NModel *model, const string &name, const string &key);
    virtual vector<string> dict_keys(NModel *model, const string &name);*/
};

#endif // STOREINTERFACE_H
