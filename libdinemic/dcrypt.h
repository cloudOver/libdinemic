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

#ifndef NCRYPT_H
#define NCRYPT_H

#include <string>
#include <libdinemic/dconfig.h>

#ifdef DINEMIC_BUILD
#include <sodium/crypto_box.h>
#include <sodium.h>
#include <boost/filesystem.hpp>
#include <sodium/crypto_secretbox.h>
#endif

class DCrypt
{
    std::map<std::string, std::string> secret_encryption_keys;
    std::map<std::string, std::string> public_encryption_keys;
    std::map<std::string, std::string> secret_sign_keys;
    std::map<std::string, std::string> public_sign_keys;

    std::string prepare_store(const std::string &key_name);
    void store_one_key(const std::string &key_name, const std::string &key, const std::string &key_type, std::map<std::string, std::string> &key_cache);
    std::string get_key(const std::string &key_name, const std::map<std::string, std::string> &keyring, const std::string &key_type);

    std::string get_secret_encryption_key(const std::string &name);
    std::string get_public_encryption_key(const std::string &name);
    std::string get_secret_sign_key(const std::string &name);
    std::string get_public_sign_key(const std::string &name);
public:
    DCrypt();
    ~DCrypt();

    /// Remove all keys from cache. This is usefull only with tests
    void clear_cache();

    /// Get combined public key pair
    std::string get_public_key(const std::string key_name);

    /// Store public keys from combined pair, in form: b64_encryption:b64_sign
    void store_public_key(const std::string key, const std::string key_name);

    std::vector<std::string> list_owned_keys();

    /// Create new pairs of encryption and sign keys. Returns the key's ID,
    /// which equals sha512(sha512(public_sign_key)).
    std::string create_keys(std::string model);

    /// Store key pair in key store. If secret key is not passed, eempty private
    /// key will be stored. This parameter is used only for keys created on
    /// local machine (i.e. by method create_key)
    void store_key(const std::string &key_name, const std::string &public_encryption_key, const std::string &public_sign_key, const std::string &secret_encryption_key=std::string(), const std::string &secret_sign_key=std::string());

    /// Create message's signature with private key key_name. Returned value is
    /// a sign method concatenated with ":" and b64 escaped value of signature.
    /// i.e.: sodium:qfu34filadanc8w...
    std::string sign(const std::string &message, const std::string &key_name);

    /// Verify message's signature created with key_name. Signature should be
    /// b64 escaped value, in format of sign method:
    /// method:b64_escaped_signature
    bool verify(const std::string &message, const std::string &signature, const std::string &key_name);

    /// Get message encrypted with public key key_name (use it to send data to
    /// receiver)
    std::string encrypt(const std::string &message, const std::string &receiver_public_key_name);

    /// Get message decrypted by private key key_name
    std::string decrypt(const std::string &message, const std::string &receiver_secret_key_name);

    std::string symmetric_encrypt(const std::string &message, const std::string &secret);

    std::string symmetric_decrypt(const std::string &message, const std::string &secret);

    std::string symmetric_create_key();


    /// Create hash of message
    std::string sha512(const std::string &message);
};

extern DCrypt dcrypt;

#endif // NCRYPT_H
