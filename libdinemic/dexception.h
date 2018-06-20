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

#ifndef NEXCEPTION_H
#define NEXCEPTION_H

#include <exception>
#include <string>

class DException : public std::exception {
    std::string reason;
public:
    DException(const std::string &reason=std::string());
    virtual std::string get_reason();
};

class DAppOptionNotFound : public DException {
public:
    DAppOptionNotFound(const std::string &reason=std::string());
};

/// Parent class for all field-related exceptions
class DUpdateRejected : public DException {
public:
    DUpdateRejected(const std::string &reason=std::string());
};

/// Throw this from DAction to prevent not verified field updates
class DFieldVerificationFailed : public DUpdateRejected {
public:
    DFieldVerificationFailed(const std::string &reason=std::string());
};

/// Throw this from DAction to prevent field updates, which are read only
class DFieldReadOnly : public DUpdateRejected {
public:
    DFieldReadOnly(const std::string &reason=std::string());
};

/// Throw this from DAction to prevent updates, which are detached from main
/// update chain or not signed
class DFieldUpdateRejected : public DUpdateRejected {
public:
    DFieldUpdateRejected(const std::string &reason=std::string());
};

/// This could be thrown by StoreInterface, if update with given ID is not found
class DUpdateNotFound : public DException {
public:
    DUpdateNotFound(const std::string &reason=std::string());
};

/// This exception is thrown by DModel constructor in case of NULL parent was
/// passed as argument
class DModelNullParent : public DException {
public:
    DModelNullParent(const std::string &reason=std::string());
};

/// This exception is thrown by DModel wen accessing non-existing element in list
/// or dict
class DModelElementNotFound : public DException {
public:
    DModelElementNotFound(const std::string &reason=std::string());
};

/// This exception is thrown by NHeaders and some Utils functions, when data is
/// malformed
class DParserError : public DException {
public:
    DParserError(const std::string &reason=std::string());
};

/// This exception is base class for DCrypt errors
class DEncryptionError : public DException {
public:
    DEncryptionError(const std::string &reason=std::string());
};

class DEncryptStoreError : public DEncryptionError {
public:
    DEncryptStoreError(const std::string &reason=std::string());
};

class DEncryptKeyExists : public DEncryptionError {
public:
    DEncryptKeyExists(const std::string &reason=std::string());
};

class DEncryptKeyNotFound : public DEncryptionError {
public:
    DEncryptKeyNotFound(const std::string &reason=std::string());
};

class DEncryptFailed : public DEncryptionError {
public:
    DEncryptFailed(const std::string &reason=std::string());
};

#endif // NEXCEPTION_H
