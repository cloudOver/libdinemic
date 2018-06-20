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

#ifndef DAPPHELPERS_H
#define DAPPHELPERS_H

#include <libdinemic/daction.h>
#include <libdinemic/sync/syncinterface.h>

namespace DAppHelpers {

    class IgnoreDetachedUpdates : public DAction
    {
    public:
        void apply(SyncInterface *sync, const std::string &filter);
        void revoke(SyncInterface *sync, const std::string &filter);
        void on_update(DActionContext &context, const std::string &key, const std::string &old_value, const std::string &new_value);
        void on_delete(DActionContext &context, const std::string key, const std::string &value);
        void on_remove(DActionContext &context);
    };

    class IgnoreUnsignedUpdates : public DAction {
    public:
        void apply(SyncInterface *sync, const std::string &filter);
        void revoke(SyncInterface *sync, const std::string &filter);
        void on_update(DActionContext &context, const std::string &key, const std::string &old_value, const std::string &new_value);
        void on_delete(DActionContext &context, const std::string key, const std::string &value);
        void on_remove(DActionContext &context);
    };

}

#endif // DAPPHELPERS_H
