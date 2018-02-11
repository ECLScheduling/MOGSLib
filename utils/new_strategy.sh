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

# Create the directory and needed files for the strategy using pre-written stubs.
mkdir $strategy_folder
cp strategy_stub "$strategy_folder/${strategy_name}Strategy.h"
cp strategy_ipp_stub "$strategy_folder/${strategy_name}Strategy.ipp"

# Swap placeholders for actual strategy name within the stubs.
sed -i -e "s/@STRATEGYNAME@/${capitalized_strategy_name}/g" "$strategy_folder/${strategy_name}.h"