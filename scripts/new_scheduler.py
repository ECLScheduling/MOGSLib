#!/usr/bin/python3

import argparse
import re
from mogslib_utils import *

### Action for consolidating a scheduler data into an intermediary python object ###
class SchedulerAction(argparse.Action):
  def __init__(self, option_strings, dest, nargs=None, **kwargs):
    super(SchedulerAction, self).__init__(option_strings, dest, nargs, **kwargs)
  def __call__(self, parser, namespace, values, option_string=None):
    current = getattr(namespace, self.dest, 2)
    if current is None:
      current = []
    current.append(Scheduler(values.pop(0), values))
    setattr(namespace, self.dest, current)

### Description of parser commands for analyzing external arguments ###
parser = argparse.ArgumentParser(description='Create a new scheduler for MOGSLib.')
parser.add_argument('-n', '--name', metavar='SchedulerName', type=str, dest='name', help='The name which will be used to select this scheduler within MOGSLib. This name must be a valid C++ variable name.')
parser.add_argument('-c', '--class', metavar='ClassName', type=str, dest='cname', help='The name of the scheduler C++ class.')
parser.add_argument('-deps', '--dependency', metavar='DependencyStructure', type=str, dest='cdeps', help='The name of the dependency structure that this scheduler will depend upon.')

args = parser.parse_args()

class NewScheduler:
  default_deps = 'MinimalDependencies'

  def __init__(self, name, cname, cdeps):
    self.name = name
    self.cname = cname
    self.cdeps = cdeps
    if name is None:
      print('The new scheduler needs a symbolic name.')
      exit(1)
    if cname is None:
      self.create_cname_from_name()
    if cdeps is None:
      self.cdeps = NewScheduler.default_deps

  def create_cname_from_name(self):
    self.cname = 'GlobalScheduler' # TODO: Make a nice heuristic here to swap _ for Uppercase and make the first letter uppercase

  def file_name(self):
    return self.name + '.h'

def copy_scheduler_stub(scheduler):
  scheduler_filename = os.path.join(MOGSLib.folders['schedulers'], new_scheduler.file_name())
  shutil.copyfile(os.path.join(MOGSLib.folders['stub'], 'scheduler.in.h'), scheduler_filename)  

def swap_stub_annotations(scheduler):
  filename = os.path.join(MOGSLib.folders['schedulers'], new_scheduler.file_name())
  with open(filename, 'r+') as infile:
    filedata = infile.read()
    filedata = filedata.replace('$CNAME$', scheduler.cname)
    filedata = filedata.replace('$TNAME$', scheduler.name)

    infile.seek(0)
    infile.truncate()
    infile.write(filedata)

def find_scheduler_enum_in_system_types():
  file = os.path.join(MOGSLib.folders['system'], 'types.h')
  scheduler_enum_line = 1             # This starts with 1 due to the null scheduler being present and the line number would invariably have to be incremented by 1.
  with open(file, 'r') as infile:
    p = re.compile('.*?SchedulerEnum.*?')
    for line in infile:
      match = p.match(line)
      if match is not None:
        return scheduler_enum_line
      scheduler_enum_line += 1
    print('Couldn\'t find the SchedulerEnum enumerate in the system/types.h file')
    exit()

def add_scheduler_to_system_types(symbolic_name):
  file = os.path.join(MOGSLib.folders['system'], 'types.h')
  lines = list()
  enumerate_line = find_scheduler_enum_in_system_types()
  
  with open(file, 'r+') as infile:
    lines = infile.readlines()

  lines[enumerate_line] += '  ' + symbolic_name + ',\n' #Warning: If the code convetion ever changes to use tabs over spaces, this method will have to be changed.

  with open(file, 'w+') as infile:
    for line in lines:
      infile.write(line)


def add_scheduler_to_traits(symbolic_name, dependency_class):
  file = os.path.join(MOGSLib.folders['system'], 'types.h')

  stub_contents = os.path.join(MOGSLib.folders['stub'], 'scheduler.in.h')
  # This function must be redone.


new_scheduler = NewScheduler(args.name, args.cname, args.cdeps)

copy_scheduler_stub(new_scheduler)
swap_stub_annotations(new_scheduler)
add_scheduler_to_system_types(new_scheduler.name)
add_scheduler_to_traits(new_scheduler.name, new_scheduler.cdeps)