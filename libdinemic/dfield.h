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

#ifndef NFIELD_H
#define NFIELD_H

#include <libdinemic/dmodel.h>
#include <string>

class DField
{
    DModel *parent;
    std::string name;
    bool encrypted;

    std::string encrypt(const std::string &value);
    std::string decrypt(const std::string &value) const;

public:
    DField(DModel *parent, const std::string &name, bool encrypted=false);
    DField &operator =(const std::string &value);
    DField &operator =(const char *value);
    DField &operator =(int value);
    DField &operator =(long value);
    DField &operator =(double value);

    bool operator ==(const char *value);
    bool operator ==(double value);
    bool operator ==(int value);
    bool operator ==(long value);


    operator std::string() const;
    operator double () const;
    operator int () const;
    operator long () const;
};

#endif // NFIELD_H
