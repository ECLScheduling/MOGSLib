#!/bin/bash

rts_name_charm="charm";
definitions_file="include/system/definitions.h"

if [ "$1" = "$rts_name_charm" ]; then
  echo "Defining constants for precompiler";
  printf "#pragma once\n\n" > "$definitions_file";

  printf "// This line states that the build is intended for the Charm environment.\n" >> "$definitions_file";
  printf "#define RTS_IS_CHARM" >> "$definitions_file";
else
  echo "Undefined RTS name"
fi;