#!/usr/bin/env bash

git submodule init
git submodule update
git submodule update --recursive

rm -vrf ./build  # If one exists, forcefully remove it
