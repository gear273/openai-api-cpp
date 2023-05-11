#!/usr/bin/env bash

make || exit
source .env
export OPENAI_API_KEY
./chat