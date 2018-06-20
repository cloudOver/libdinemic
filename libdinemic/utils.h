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

#ifndef UTILS_H
#define UTILS_H

#include <unistd.h>

#include <map>
#include <vector>
#include <string>
#include <array>

#include <cstdio>
#include <memory>
#include <stdexcept>

#include <iostream>
#include <fstream>
#include <sstream>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#include <libdinemic/dconfig.h>
#include <libdinemic/dheaders.h>
#include <libdinemic/dexception.h>
#include <libdinemic/dcrypt.h>
#include <libdinemic/logger.h>

#ifdef DINEMIC_BUILD
#include <boost/archive/iterators/binary_from_base64.hpp>
#include <boost/archive/iterators/base64_from_binary.hpp>
#include <boost/archive/iterators/transform_width.hpp>
#include <boost/algorithm/string.hpp>
#endif

#define ID_LEN 32

class DHeaders;

namespace Utils {
    void initialize_env();
    void initialize_log();
    void initialize_gpg();

    std::vector<std::string> split(const std::string &input, const std::string &token);
    std::string join(std::vector<std::string> &items, const std::string token);
    std::string exec(const std::string &cmd);

    std::string generate_id();

    std::string escape_value(const std::string &value);
    std::string unescape_value(const std::string &value);

    std::string timestamp();
}

#endif // UTILS_H
