#!/bin/bash

################## Declaring Constants #####################
declare -a rts_list=("none" "charm" "openmp");
declare -a rts_capitalized_list=("None" "Charm" "OpenMP");
declare -a rts_def_list=("RTS_IS_NONE" "RTS_IS_CHARM" "RTS_IS_OPENMP");

declare rts_list_size=${#rts_list[@]}
declare rts_file="include/rts/rts_includes.h";

declare found_rts=0;
############################################################

####### Pre-declaring variables used in configuration ######
declare RTS_NAME=""
declare CAPS_RTS_NAME=""

declare STRATEGY_NAME=""
declare CAPS_STRATEGY_NAME=""

declare ADAPTOR_NAME=""
declare CAPS_ADAPTOR_NAME=""

declare ADAPTOR_TEMPLATES=""
############################################################

####### Print Help Function ################################
function PRINT_HELP {
  echo "Correct Usage:"
  echo -e "  -s, --strategy [strategy_name]\t\tSet a target strategy in the rts_includes.h file."
  echo -e "  -a, --adaptor [adaptor_name]\t\t\tSet a target adaptor in the rts_includes.h file."
  echo -e "  -at, --adaptor-template [t1_t2_t3]\t\tSet a list of template parameters separated by '_' to formulate the adaptor in the rts_includes.h file."
  echo -e "  -rts, --runtimesystem [rts_name]\t\tSet a target RTS in the rts_includes.h file and definitions.h file."
  echo -e "\nStart the names with lower case. If the name contains an uppercase after the first letter, this letter must be capitalized."
  echo -e "The strategy and adaptor names can be found in the include directory under the respective subdirectories"
  echo -e "The current supported RTS names are: 'charm' and 'openmp'"
  exit 0
}
############################################################

################# Parse Arguments ##########################
declare POSITIONAL=()

function PARSE_PARAMS {
while [[ $# -gt 0 ]]
do
key="$1"
case $key in
  -s|--strategy)
  STRATEGY_NAME="$2"
  shift
  shift
  ;;
  -a|--adaptor)
  ADAPTOR_NAME="$2"
  shift
  shift
  ;;
  -at|--adaptor-template)
  ADAPTOR_TEMPLATES="$2"
  shift
  shift
  ;;
  -rts|--runtimesytem)
  RTS_NAME="$2"
  shift
  shift
  ;;
  -h|--help)
  PRINT_HELP
  ;;
  *)
  POSITIONAL+=("$1")
  shift
  ;;
esac
done
}
############################################################

################# Finding the target RTS ###################
function PREPARE_TO_RTS {
echo "Parsing target RTS...";
for((i=0; i<${rts_list_size}; i++));
do
  if [ $RTS_NAME == ${rts_list[i]} ]; then
    found_rts=1;
    CAPS_RTS_NAME=${rts_capitalized_list[i]}

    cp scripts/stubs/rts_includes.stub "$rts_file"
    
    # Swap RTS placeholders
    sed -i -e "s/@CAPS_RTS_NAME@/${CAPS_RTS_NAME}/g" "$rts_file"
    sed -i -e "s/@RTS_NAME@/${RTS_NAME}/g" "$rts_file"
    sed -i -e "s/@RTS_NAME_DEFINE@/${rts_def_list[i]}/g" "$rts_file"

    echo -e "\tTarget RTS set to ${rts_capitalized_list[i]}.";
  fi
done

if [ $found_rts -eq 0 ]; then
  echo -e "\tCould not identify the target RTS. Exiting...";
  exit 1;
fi
}
#############################################################

############### Finding a target Strategy ###################
function PREPARE_TO_STRATEGY {
echo "Parsing target Strategy...";
CAPS_STRATEGY_NAME="${STRATEGY_NAME^}"

# Swap Strategy placeholders
sed -i -e "s/@CAPS_STRATEGY_NAME@/${CAPS_STRATEGY_NAME}/g" "$rts_file"
sed -i -e "s/@STRATEGY_NAME@/${STRATEGY_NAME}/g" "$rts_file"

echo -e "\tStrategy set to ${CAPS_STRATEGY_NAME}Strategy.";
}
#############################################################

############### Finding a target Adaptor ####################
function PREPARE_TO_ADAPTOR {
echo "Parsing target Adaptor...";
CAPS_ADAPTOR_NAME="${ADAPTOR_NAME^}"

# Swap Adaptor placeholders
sed -i -e "s/@CAPS_ADAPTOR_NAME@/${CAPS_ADAPTOR_NAME}/g" "$rts_file"
echo -e "\tAdaptor set to ${CAPS_ADAPTOR_NAME}.";
}
#############################################################

############ Resolving an Adaptor Templates #################
function PREPARE_TO_ADAPTOR_TEMPLATES {
ADAPTOR_TEMPLATES="$(sed "s/_\(.\)/, \U\1/g" <<< ${ADAPTOR_TEMPLATES})"
ADAPTOR_TEMPLATES="<${ADAPTOR_TEMPLATES^}>"

echo -e "\tAdaptor templates set to ${ADAPTOR_TEMPLATES}.";
}
#############################################################

############ Actual Script ##################################

# Go to the home dir for the script to work properly.
BASEDIR=$(dirname "$0")
cd $BASEDIR/..

# Parse Params
PARSE_PARAMS $@;

# Parse RTS
PREPARE_TO_RTS;

# Parse Strategy
if [ "$STRATEGY_NAME" != "" ]; then
  PREPARE_TO_STRATEGY;
fi

# Parse Adaptor
if [ "$ADAPTOR_NAME" != "" ]; then
  PREPARE_TO_ADAPTOR;
  
  # Parse Adaptor templates
  if [ "$ADAPTOR_TEMPLATES" != "" ]; then
    PREPARE_TO_ADAPTOR_TEMPLATES;
  fi
  
  # Swap Adaptor template placeholders
  sed -i -e "s/@ADAPTOR_TEMPLATES@/${ADAPTOR_TEMPLATES}/g" "$rts_file"
fi

# Save the command line for future use
echo $@ > config_script_args.txt