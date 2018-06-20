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
#ifndef NMODEL_H

#define NMODEL_H

#include <map>
#include <mutex>
#include <string>
#include <unordered_map>
#include <vector>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libdinemic/sync/syncinterface.h>
#include <libdinemic/store/storeinterface.h>
#include <libdinemic/utils.h>
#include <libdinemic/dconfig.h>
#include <libdinemic/dexception.h>
#include <libdinemic/dcrypt.h>

class DModel
{
    StoreInterface *_store;
    SyncInterface *_sync;
    DModel *_parent;
    bool _delete_parent;

    std::string _id;
    std::mutex lock;

    /// Get caller. This method is used to obtain proper object updating
    /// fields. i.e. another object could update this object (another's key
    /// will be used)
    DModel *get_caller(DModel *caller);

    void init_model(const std::vector<std::string> &authorized_object_ids);
protected:
    std::string _model;

    /// Lock this instance of object (node-wide)
    void _lock();

    /// Unlock this instance of object (node wide)
    void _unlock();

public:
    /**
     * @brief NObject ReCreate existing object from given ID. Use this
     * constructor to retreive any kind of models and cast created object to the
     * proper type. Any kind of data should not contain internal, additional
     * fields. Instead, use provided get/set/del/iterate methods from NObject
     * class.
     * @param store Pointer to valid StoreInterface instance
     * @param sync Pointer to valid SyncInterface instance
     * @param id ID of object
     * @param parent parent object
     */
    DModel(const std::string &db_id, StoreInterface *store, SyncInterface *sync, DModel *parent=NULL);

    /**
     * @brief NModel Create new object inside another
     * @param model_name Name of child model
     * @param parent Pointer to parent object
     */
    DModel(std::string model_name, DModel *parent);

    /**
     * @brief NModel Create new object in database
     * @param model_name Name of model
     * @param store Pointer to StoreInterface instance
     * @param sync Pointer to SyncInterface instance
     * @param authorized_object_ids List of objects authorized to update this model and read encrypted data through DField
     */
    DModel(std::string model_name,
           StoreInterface *store,
           SyncInterface *sync,
           const std::vector<std::string> &authorized_object_ids);

    virtual ~DModel();

    /// Get object ID string
    std::string get_id();

    /// Get object ID used in database in form: model:id
    std::string get_db_id();

    /// Get model's name
    std::string get_model();

    StoreInterface *get_store_interface();
    SyncInterface *get_sync_interface();

    static std::vector<std::string> object_list_owned(std::string filter, StoreInterface *_store);
    std::vector<std::string> object_list_owned(std::string filter="");
    static std::vector<std::string> object_list(std::string filter, StoreInterface *_store);
    std::vector<std::string> object_list(std::string filter="");

    /// Get property's value from model
    virtual std::string get(const std::string key, const std::string &def="", DModel *parent=NULL);

    /// Set property's value
    virtual void set(const std::string &key, const std::string &value, DModel *parent=NULL);

    /// Delete property
    virtual void del(const std::string key, DModel *parent=NULL);

    /// Get list of all properties
    virtual std::vector<std::string> keys(DModel *parent=NULL);

    /// Insert element to the list
    virtual std::string list_insert(const std::string &name, long index, const std::string &value, DModel *parent=NULL);

    /// Append element at the end of list
    virtual std::string list_append(const std::string &name, const std::string &value, DModel *parent=NULL);

    /// Update value of existing element in list
    virtual std::string list_set(const std::string &name, long index, const std::string &value, DModel *parent=NULL);

    /// Get element at index
    virtual std::string list_at(const std::string &name, long index, DModel *parent=NULL);

    /// Get list size
    virtual long list_length(const std::string &name, DModel *parent=NULL);

    /// Delete element
    virtual void list_delete(const std::string &name, long index, DModel *parent=NULL);

    /// Get position of element in list. Returns -1 if element is not found
    virtual long list_index(const std::string &name, const std::string &value);

    /// Encrypt data for all encryption_keys assigned to this object
    std::string encrypt(std::string value);

    /// Decrypt data with object's private key
    std::string decrypt(std::string value);

    //void iterate_items(void(*iterator)(const std::string key, void *data));
};

#endif // NMODEL_H
