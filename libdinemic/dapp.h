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

#ifndef DAPP_H
#define DAPP_H

#include <stdlib.h>
#include <time.h>
#include <libdinemic/utils.h>
#include <libdinemic/logger.h>
#include <libdinemic/store/storeinterface.h>
#include <libdinemic/store/memorydriver.h>
#include <libdinemic/store/redisdriver.h>
#include <libdinemic/sync/syncinterface.h>
#include <libdinemic/sync/zeromqsync.h>

enum DAppOptionMode {
    DAppOptionMode_any,
    DAppOptionMode_create,
    DAppOptionMode_launch,
    DAppOptionMode_oneshot,
    DAppOptionMode_remove,
};

class DAppOption
{
public:
    std::string short_name;
    std::string long_name;
    std::string help;
    bool is_switch;
    bool is_present;
    DAppOptionMode mode;
    std::vector<std::string> values;
};

class DApp
{
private:
    std::string application_name, application_description;
    int argc;
    char **argv;
    bool is_running;

    std::vector<DAppOption> options;

    void parse_options();
    friend class TestDAppOptions;

protected:
    StoreInterface *store;
    SyncInterface *sync;

    /**
     * @brief add_option Add new option to program
     * @param short_name Short (switch) name of option, i.e. -m
     * @param long_name Long option name, i.e. --mode
     * @param help Help text for option
     * @param is_switch If true, option does not take a value
     * @param mode Defines if option could be used in given mode (launch/create/remove/oneshot)
     */
    void add_option(const std::string &short_name, const std::string &long_name, const std::string &help, bool is_switch=false, DAppOptionMode mode=DAppOptionMode_any);

    /**
     * @brief get_option Get all occurances of option
     * @param name Short or long name
     * @return DAppOption object with matching option
     */
    DAppOption get_option(const std::string &name);

    /**
     * @brief has_option Return true if option is present in parameters
     * @param name Short or long name of option
     */
    bool has_option(const std::string &name);

public:
    DApp(int argc, char **argv, const std::string &application_name, const std::string &application_description);
    ~DApp();

    /**
     * Create new objects in database here. Each call of this method on app
     * creates new set of objects.
     */
    virtual void create();

    /**
     * Create new DAction listeners here and map them with proper obejcts and
     * updates of database. Update states of owned models here too. This is main
     * loop for application
     */
    virtual void launch();

    /**
     * This is place for all one-time actions in your applications. It does not
     * enter into main loop.
     */
    virtual void oneshot();

    /**
     * Notify about stopping this DB Node. Use this method to update states of
     * handled objects.
     */
    virtual void stop();

    /**
     * Remove object from database
     */
    virtual void remove();

    /**
     * Call this method to run application, all agents and handle all DB updates/
     * Don't override this method on your class!
     */
    int exec();
};

#endif // DAPP_H
