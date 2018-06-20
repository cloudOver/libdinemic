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

#ifndef NACTION_H
#define NACTION_H

#include <iostream>
#include <string>
#include <map>
#include <libdinemic/utils.h>
#include <libdinemic/dheaders.h>

class DModel;
class SyncInterface;
class DHeaders;

class DActionContext {
    /// If true, notification was verified by one of object's authorized keys
    std::vector<bool> verified;

    /// If true, notification has no predecessor
    bool detached;

    /// List of IDs of objects, which signed this update
    std::vector<std::string> caller_ids;

    /// List of public keys, which signed this update
    std::vector<std::string> sign_keys;

    DHeaders *headers;
    DModel *object;

public:
    DActionContext();
    DActionContext(std::vector<std::string> caller_ids,
                 std::vector<std::string> sign_keys,
                 std::vector<bool> verified,
                 bool detached,
                 DHeaders *headers,
                 DModel *object);

    /// Returns true if update was verified by the last Signature field and there
    /// is no more fields after last Signature
    bool is_verified() const;

    /// Returns True if Previous field is set to none. It means the detached
    /// update from any update chain.
    bool is_detached() const;

    /// Get IDs of objects, which created update related to this action flags
    /// instance
    std::vector<std::string> get_caller_ids();

    /// Get keys used to verify update
    std::vector<std::string> get_sign_keys();

    /// Get all flags for action. Each Signature header creates one entry in list
    /// returned by this method. One Update could contain multiple Signature
    /// fields, thus this checks all of them
    std::vector<bool> get_verified_flags();

    /// Get headers related to action
    DHeaders &get_headers();

    /// Get object related to action
    DModel &get_object();
};


class DAction
{
public:
    DAction();

    /// Override this method to allow simple adding your own DAction class to
    /// sync. This method should add DAction to proper methods and models
    virtual void apply(SyncInterface *sync, const std::string &filter);

    virtual void revoke(SyncInterface *sync, const std::string &filter);

    /// General method called on the object's instance when any related to model
    /// object was created in DB. This should be called only by SyncInterface
    virtual void on_create(DActionContext &context, const std::string &key);
    virtual void on_created(DActionContext &context, const std::string &key);

    /// General method called on the object's instance when any related to model
    /// object was updated in DB. This should be called only
    /// by sync SyncInterface
    virtual void on_update(DActionContext &context, const std::string &key, const std::string &old_value, const std::string &new_value);
    virtual void on_updated(DActionContext &context, const std::string &key, const std::string &old_value, const std::string &new_value);

    /// General method called on the object's instance, when object is about to
    /// object's field was removed in DB
    virtual void on_delete(DActionContext &context, const std::string key, const std::string &value);
    virtual void on_deleted(DActionContext &context, const std::string key, const std::string &value);

    /// General method called on the object's instance, when object is about to
    /// be removed from database. This should be called only by SyncInterface
    virtual void on_remove(DActionContext &context);
};

#endif // NACTION_H
