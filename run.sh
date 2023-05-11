#!/usr/bin/env bash

make chat || exit
source .env
export OPENAI_API_KEY
./build/chat