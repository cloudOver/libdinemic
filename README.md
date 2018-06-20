# libdinemic
Libdinemic is a framework for creating distributed and decentralized applications, based on cryptography. you can easily create applications running on different hosts, without carrying on database, connectivity and API. Libdinemic provides support for all those functionalities, including:
 * Node autodiscovery
 * Authentication
 * Database versioning
 * Security
 * Redundancy

Project website: https://dinemic.io

Compilation
===========
Use script `build.sh` to create Debian packges for Libdinemic. You will need lintian, dpkg-dev and some other dependency packages. Most of them will be shown after running only the `build.sh` script.

Intallation
===========
Download precompiled package from https://packages.dinemic.io. Then use `aptitude install libdinemic-[version].deb` to install this library in your system. Aptitude will resolve all dependencies for your system.

On Rpm based systems, use rpm to instal proper package.

Documentation
=============
See the `docs/` directory for documentation and `examples/` for code examples.
