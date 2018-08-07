#!/usr/bin/python3

import os
import shutil
import re

### Define the creation of a map of attributes that will aid the configuration of the RTS data in MOGSLib ###
def rts_custom():
  print('Undefined Configure Procedure for Custom RTS')
  exit()

def rts_charm():
  return {
    'RTS_ENUM_VAL': 'Charm',
    'RTS_INCLUDES': (
      'mogslib/rts/charm.h',
      'mogslib/rts/charm.ipp'
      )
  }

def rts_openmp():
  return {
    'RTS_ENUM_VAL': 'OpenMP',
    'RTS_INCLUDES': (
      'mogslib/rts/openmp.h',
      'mogslib/rts/openmp.ipp'
      )
  }

def rts_invalid():
  print("Invalid RTS name")
  exit()


### Mapping from the possible RTS argument values into functions to set up MOGSLib configuration data for the RTS ###
rts_config_map = {
  'custom': rts_custom,
  'charm': rts_charm,
  'openmp': rts_openmp
}

def get_rts_config_map(rts):
  return rts_config_map.get(rts, rts_invalid)()


### Define the functions that will manipulate MOGSLib stub files to set up the RTS data types ###

def pre_custom(dict):
  print("Invalid Install procedure for Custom RTS")
  exit()

def pre_default(dict):
  include_dir = os.path.join(os.path.dirname(os.path.dirname(os.path.realpath(__file__))), 'include')
  system_dir = os.path.join(include_dir, 'system')
  stub_dir = os.path.join(os.path.dirname(os.path.realpath(__file__)), 'stubs')
  mogslib_dir = os.path.join(include_dir, 'mogslib')

  print('Preparing MOGSLib for the ' + dict['RTS_ENUM_VAL'] + ' Runtime System')
  print('\tDefining RTS traits in system/type_definitions.h')
  
  file = os.path.join(system_dir, 'type_definitions.h')
  shutil.copyfile(os.path.join(stub_dir, 'type_definitions.in.h'), file)
  with open(file, 'r+') as infile:
    filedata = infile.read()
    filedata = filedata.replace('@RTS_ENUM_VAL@', dict['RTS_ENUM_VAL'])
    infile.seek(0)
    infile.truncate()
    infile.write(filedata)

  print('\tDefining RTS abstraction for MOGSLib components in mogslib/mogslib.h')

  file = os.path.join(mogslib_dir, 'mogslib.h')
  shutil.copyfile(os.path.join(stub_dir, 'mogslib.in.h'), file)
  include_string = ''
  for rts_include in dict['RTS_INCLUDES']:
    include_string += '#include <' + rts_include + '>\n'
  with open(file, 'r+') as infile:
    filedata = infile.read()
    filedata = filedata.replace('@RTS_INCLUDES@', include_string)
    infile.seek(0)
    infile.truncate()
    infile.write(filedata)

  print('RTS is set for ' + dict['RTS_ENUM_VAL'])


### Mapping from the possible RTS argument values into functions to create the MOGSLib Definitions and Type Definitions ###
rts_precompile = {
  'custom': pre_custom,
  'charm': pre_default,
  'openmp': pre_default
}

def generate_defs_for_rts(rts):
  return rts_precompile.get(rts, rts_invalid)(get_rts_config_map(rts))