#!/usr/bin/python3

from mogslib_utils import *
import re

included_concepts = dict()
std_natives = ('int', 'double', 'char', 'float')

def find_sched_class_name(sched_name):
  folders = MOGSLib.folders
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
        classname = 'SchedulerDecl(' + match.group(1) + ')'
        break
  return classname

def find_adapters_class_names(concepts):
  folders = MOGSLib.folders
  concept_classes = []

  for concept in concepts:
    if concept in std_natives:
      concept_classes.append(concept)
      continue
    file = os.path.join(folders['concepts'], 'concrete', concept + '.h')
    if not os.path.isfile(file):
      print('Concrete Concept \'' + concept + '\' was not found in MOGSLib.')
      exit()

    with open(file, 'r') as infile:
      p = re.compile('class\s+(\w+)\s+:\s+public\s+Abstraction::Concept')
      for line in infile:
        match = p.match(line)
        if match is not None:
          concept_classes.append('ConceptDecl(' + match.group(1) + ')')
          break
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
    ret += 'TupleGetSnippet(' + adapter + ', ' + str(i) + ')\n    ' #Warning: The 4 spaces should be swapped for 2 tabs if the project code style ever changes to tabs.
    i += 1
  ret = ret[:-5] #Warning: Read the warning above.
  return ret

def configure_schedulers(scheds, rts_name):
  folders = MOGSLib.folders
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
      concept_index = 0
      if concept not in included_concepts:
        print('\tImporting \'' + concept + '\' Concept to MOGSLib definitions.')
        concept_includes += '#include <concepts/concrete/' + concept + '.h>\n'
        concept_includes += '#include <concepts/init/' + rts_name + '/' + concept + '.ipp>\n'
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