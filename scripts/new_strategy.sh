#!/bin/bash

### Script Input ###
strategy_name="$1";
### End of Input ###

# Go to the utils dir for the script to work properly.
BASEDIR=$(dirname "$0")
cd $BASEDIR

# Get the strategy name from script parameter or default.
capitalized_strategy_name="${strategy_name^}"

# Formulate a directory name for the new strategy within the proper place in the library.
strategy_folder="../include/strategies/${strategy_name}"
algorithms_folder="../include/algorithms/${strategy_name}"

# Create the directory and needed files for the strategy using pre-written stubs.
mkdir -p $strategy_folder
mkdir -p $algorithms_folder
cp "stubs/strategy.h.in" "$strategy_folder/${strategy_name}Strategy.h"
cp "stubs/strategy_ipp.h.in" "$strategy_folder/${strategy_name}Strategy.ipp"
cp "stubs/algorithm_stub.h.in" "$algorithms_folder/${strategy_name}Algorithm.h"

# Swap placeholders for actual strategy name within the stubs.
sed -i -e "s/@STRATEGYNAME@/${capitalized_strategy_name}/g" "$strategy_folder/${strategy_name}Strategy.h"
sed -i -e "s/@STRATEGYNAME@/${capitalized_strategy_name}/g" "$algorithms_folder/${strategy_name}Algorithm.h"