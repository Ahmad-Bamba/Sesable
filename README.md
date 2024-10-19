# Sesable -- fast, lightweight, organization-based encrypted notes.

## Core idea
You launch an instance of this web app on a server somewhere and you have the ability to log in.
Once you do, you can create an "organization".
Creating an organization automatically makes you a member of one.
The organization's name is hashed client-side and sent to the server.
Under the organization, you can create named tables of arbitary information that are also hased client-side and sent to the server.
New accounts can ask to join the organization if they know the organization name and if all previous members of the organization accept.
Accounts can be removed from organizations if all other members of the organization agree.
Any member of an organization can add or delete an organization's tables.

## Use case
Small organizations or individuals that want a private, secure, and democratized solution to storing sensitive information that they
completely control.

Like [cryptpad](https://cryptpad.fr/), but with the goal of focusing on notes and tables, not trying to recreate a full office suite.
The goal of being faster, more lightweight, and dead simple to install on any webserver or locally.

## Build dependencies and instructions
To build you will need:
- cmake (at least version 3.22) and vcpkg
- node (version 18 or later), npm, and npx in your path

It is also strongly recommended to have the following programs in your path:
- clang-tidy

And optional to have the following programs in your path:
- cppsafe\*

\* Planned for use future lifetime checks on the backend but not currently used.

The easiest way to get started is to create a CMakeUserPresets.json file in the root of the project.
Read through the CMakePresets.json and choose a preset to inherit from. 

Currently the presets are:
- default: Builds an optimized build with debug info, with unit tests and extra linting turned on. Useful for development.
- release: Builds optimized Sesable applicaiton only.

If you don't have vcpkg, but have all the other dependencies you can also install all the dependencies listed in vcpkg.json manually, and
build CMake normally.

## Installation

TODO: