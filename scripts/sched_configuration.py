#!/usr/bin/python3

from mogslib_utils import *
import re

included_concepts = dict()

def find_sched_class_name(sched_name):
  folders = MOGSLib.folders
  file = os.path.join(folders['schedulers'], sched_name + '.h')
  classname = ''

  if not os.path.isfile(file):
    print('Scheduler \'' + sched_name + '\' was not found in MOGSLib.')
    exit()

  with open(file, 'r') as infile:
    p = re.compile('(class|struct)\s+(\w+)\s+:\s+public\s+Abstraction::Scheduler')
    for line in infile:
      match = p.match(line)
      if match is not None:
        classname = 'SchedulerDecl(' + match.group(2) + ')'
        break
    if not classname:
      print('Scheduler \'' + sched_name + '\' could not be identified as a C++ class.')
      exit()
  return classname


def find_adapters_class_names(concepts):
  folders = MOGSLib.folders
  concept_classes = []

  for concept in concepts:
    file = os.path.join(folders['concepts'], 'implementation', concept + '.h')
    if not os.path.isfile(file):
      print('Concrete Concept \'' + concept + '\' was not found in MOGSLib.')
      exit()

    with open(file, 'r') as infile:
      p = re.compile('(class|struct)\s+(\w+)\s+[{:]')
      found = False
      for line in infile:
        match = p.match(line)
        if match is not None:
          concept_classes.append('ConceptDecl(' + match.group(2) + ')')
          found = True
          break
      if not found:
        print('Concrete Concept \'' + concept + '\' could not be identified as a C++ class nor struct.')
        exit()
  return concept_classes

def generate_scheduler_tuple_code(names, concepts):
  ret = ''
  for i in range(0, len(names)):
    ret += 'SchedulerTupleDef(' + names[i]
    if concepts[i]:
      ret += ', '
      for concept in concepts[i]:
        ret += concept + ', '
      ret = ret[:-2]
    ret += '), '
  return ret[:-2]

def generate_schedule_function_code(n):
  ret = ''
  for i in range(0, n):
    ret += '\t\tScheduleSnippet(' + str(i) + ')\n'
  return ret[:-1]

def generate_tupleget_specs(adapters):
  ret = ''
  i = 0
  for adapter in adapters:
    ret += 'TupleGetSnippet(' + adapter + ', ' + str(i) + ')\n'
  ret = ret[:-1]
  return ret

def configure_schedulers(scheds, rts_name):
  folders = MOGSLib.folders
  file = os.path.join(folders['mogslib'], 'mogslib.h')

  sched_includes = ''
  concept_includes = ''
  sched_names = []
  sched_adapters = []
  for sched in scheds:
    print('\nConfiguring \'' + sched.name + '\' scheduler to work within the \'' + rts_name + '\' runtime system.')
    sched_includes += '#include <schedulers/' + sched.name + '.h>\n'

    sched_names.append(find_sched_class_name(sched.name))
    sched_adapters.append(find_adapters_class_names(sched.concepts))

    for concept in sched.concepts:
      concept_index = 0
      if concept not in included_concepts:
        print('\tSetting \'' + concept + '\' drivers for \'' + rts_name + '\' in MOGSLib definitions.')

        test_concept_file = os.path.join(folders['concepts'], 'driver', rts_name, concept + '.ipp')
        if os.path.isfile(test_concept_file):
          concept_includes += '#include <concepts/driver/' + rts_name + '/' + concept + '.ipp>\n'
        else:
          print('\t\tDriver specialization for \'' + concept + '\' in \'' + rts_name + '\' RTS was not found in MOGSLib.')
        included_concepts[concept] = concept_index

  adapters_class_names = find_adapters_class_names(included_concepts.keys())
  with open(file, 'r+') as infile:
    filedata = infile.read()
    filedata = filedata.replace('@SCHED_INCLUDES@', sched_includes)
    filedata = filedata.replace('@CONCEPT_INCLUDES@', concept_includes)

    filedata = filedata.replace('$SCHEDULER_TUPLE$', generate_scheduler_tuple_code(sched_names, sched_adapters))
    filedata = filedata.replace('$SCHEDULE_SNIPPET$', generate_schedule_function_code(len(sched_names)))
    filedata = filedata.replace('$CONCEPT_TUPLE$', ', '.join(adapters_class_names))
    filedata = filedata.replace('$TUPLE_GET_SPECS$', generate_tupleget_specs(adapters_class_names))
    infile.seek(0)
    infile.truncate()
    infile.write(filedata)