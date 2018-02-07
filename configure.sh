#!/bin/bash

declare -a rts_list=("charm" "openmp");
declare -a rts_def=("RTS_IS_CHARM" "RTS_IS_OPENMP");

declare rts_list_size=${#rts_list[@]}
declare definitions_file="include/system/definitions.h";

declare found_rts=0;

echo "Checking target RTS...";
for((i=0; i<${rts_list_size}; i++));
do
  if [ "$1" == ${rts_list[i]} ]; then
    found_rts=1;
    echo "Target RTS is ${rts_list[i]}";
    echo "#pragma once" > ${definitions_file}
    echo "#define ${rts_def[i]}" >> ${definitions_file}
  fi
done

if [ $found_rts -eq 0 ]; then
  echo "Could not identify the target RTS";
fi