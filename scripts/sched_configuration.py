#!/usr/bin/python3

from mogslib_utils import *
import re

included_concepts = []

def find_sched_class_name(sched_name):
  folders = get_folder_map()
  file = os.path.join(folders['schedulers'], sched_name + '.h')
  classname = ''

  if not os.path.isfile(file):
    print('Scheduler \'' + sched_name + '\' was not found in MOGSLib.')
    exit()

  with open(file, 'r') as infile:
    p = re.compile('class\s+(\w+)\s+:\s+public\s+Abstraction::Scheduler')
    for line in infile:
      match = p.match(line)
      if match is not None:
        classname = match.group(1)
        break
  return classname


def find_adapters_class_names(concepts):
  folders = get_folder_map()
  concept_classes = []

  for concept in concepts:
    file = os.path.join(folders['concepts'], 'concrete', concept + '.h')
    if not os.path.isfile(file):
      print('Concrete Concept \'' + concept + '\' was not found in MOGSLib.')
      exit()

    with open(file, 'r') as infile:
      p = re.compile('class\s+(\w+)\s+:\s+public\s+Abstraction::Concept')
      for line in infile:
        match = p.match(line)
        if match is not None:
          concept_classes.append('MOGSLib::Concept::' + match.group(1))
          break
  return concept_classes

def create_adapters_typedefs(adapter_list):
  typedefs = []
  c = 0
  for adapter in adapter_list:
    typedefs.append('\tusing Adapter' + str(c) + ' = ' + adapter + ';')
    c += 1
  return '\n'.join(typedefs)

def configure_schedulers(scheds, rts_name):
  folders = get_folder_map()
  file = os.path.join(folders['mogslib'], 'mogslib.h')

  sched_includes = ''
  concept_includes = ''
  sched_names = []
  sched_adapters = []
  for sched in scheds:
    print('\nConfiguring Scheduler \'' + sched.name + '\' to work within \'' + rts_name + '\' Runtime System.')
    sched_includes += '#include <schedulers/' + sched.name + '.h>\n'

    sched_names.append(find_sched_class_name(sched.name))
    sched_adapters.append(find_adapters_class_names(sched.concepts))

    for concept in sched.concepts:
      if concept not in included_concepts:
        print('\tImporting \'' + concept + '\' Concept to MOGSLib definitions.')
        concept_includes += '#include <concepts/concrete/' + concept + '.h>\n'
        concept_includes += '#include <concepts/init/' + rts_name + '/' + concept + '.ipp>\n'
        included_concepts.append(concept)

  with open(file, 'r+') as infile:
    filedata = infile.read()
    filedata = filedata.replace('@SCHED_INCLUDES@', sched_includes)
    filedata = filedata.replace('@CONCEPT_INCLUDES@', concept_includes)
    filedata = filedata.replace('@SCHED_NAME@', sched_names[0])
    filedata = filedata.replace('@SCHED_ADAPTERS@', ', '.join(sched_adapters[0]))
    filedata = filedata.replace('@ADAPTERS_TYPEDEFS@', create_adapters_typedefs(sched_adapters[0]))
    infile.seek(0)
    infile.truncate()
    infile.write(filedata)