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

def add_scheduler_to_types_enum(scheduler):
  file = os.path.join(MOGSLib.folders['system'], 'types.h')
  enums = 'no match'
  with open(file, 'r') as infile:
    filedata = infile.read()
    p = re.compile(r"(.*)", re.MULTILINE) #TODO: check this regex out
    match = p.match(filedata)
    print(match)
    if match is not None:
      enums = match.group(1)
  print(enums)

new_scheduler = NewScheduler(args.name, args.cname, args.cdeps)

#copy_scheduler_stub(new_scheduler)
#swap_stub_annotations(new_scheduler)
add_scheduler_to_types_enum(new_scheduler)