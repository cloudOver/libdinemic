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

#ifndef NHEADERS_H
#define NHEADERS_H

#include <vector>
#include <string>

#ifdef DINEMIC_BUILD
#include <boost/range/adaptor/reversed.hpp>
#endif

#define HEADER_ID "ID"
#define HEADER_PREVIOUS "Previous"
#define HEADER_PREVIOUS_HASH "Previous-Hash"
#define HEADER_PREVIOUS_HASH_METHOD "Previous-Hash-Method"
#define HEADER_SIGNATURE "Signature"
#define HEADER_SIGNATURE_METHOD "Signature-Method"
#define HEADER_CALLER "Caller"
#define HEADER_TIMESTAMP "Timestamp"
#define HEADER_NEXT "Next"
#define HEADER_ROUTE_TO "Route-To"
#define HEADER_ROUTE_FROM "Route-From"
#define HEADER_ACTION "Action"
#define HEADER_OBJECT "Object"
#define HEADER_KEY "Key"
#define HEADER_FIELD "Field"
#define HEADER_VALUE "Value"
#define HEADER_INDEX "Index"

class DModel;

#include <libdinemic/utils.h>
#include <libdinemic/daction.h>

class DActionContext;

class ID {
    std::vector<std::string> parts;
public:
    ID(std::string id);
    std::string get_parent();
    std::string get_full_id();
    std::vector<std::string> get_parts();
    std::string get_object_id();
    std::string get_object_model();
    std::string to_path();
    bool is_valid();
    bool has_parent();
};

class DHeaders
{
    std::vector<std::pair<std::string, std::string> > headers;
public:
    DHeaders();
    DHeaders(const std::string &update);

    std::string sign(const std::string &key_name);
    DActionContext verify(bool chained, DModel *obj);

    /// Get last occurance of field in headers
    std::string operator [](const std::string &field) const;

    /// Get all occurances of field in headers
    std::vector<std::string> get_all(const std::string &field);

    void add(const std::string &field, const std::string &value);

    std::vector<std::string> fields();

    /// Get DHeaders as string with all fields
    std::string to_string() const;

    /// Get DHeaders as string with all fields except Route-To, Route-From
    /// and Next fields, which are added by SyncInterface when message arrives or
    /// next message in chain arrives. This method is used to calculate hash,
    /// and it contains Signature field.
    std::string to_string_unrouted() const;

    /// Get DHeaders as string with all fields except Route-To, Route-From,
    /// Next fields, and without signatures. This method is used to calculate signature
    std::string to_string_unsigned() const;

    size_t size();
};

#endif // NHEADERS_H
