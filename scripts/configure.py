#!/usr/bin/python3

import argparse
import re
import os
import shutil

### Scheduler class that contains all the data needed to express a scheduler in MOGSLib ###
class Scheduler:
  def __init__(self, name, context):
    self.name = name
    self.context = context

### Top level class to hold information about the library. ###
class MOGSLib:
  folders = dict()

  def init():
    MOGSLib.folders['schedulers'] = 'schedulers'

    MOGSLib.folders['abstractions'] = 'abstractions'
    MOGSLib.folders['contexts'] = os.path.join(MOGSLib.folders['abstractions'], 'contexts')
    MOGSLib.folders['traits'] = os.path.join(MOGSLib.folders['abstractions'], 'traits')

    MOGSLib.folders['stub'] = os.path.join(os.path.dirname(os.path.realpath(__file__)), 'stubs')
    MOGSLib.folders['include_abs'] = os.path.join(os.path.dirname(os.path.dirname(os.path.realpath(__file__))), 'include')
    MOGSLib.folders['mogslib_abs'] = os.path.join(MOGSLib.folders['include_abs'], 'mogslib')
    MOGSLib.folders['abstractions_abs'] = os.path.join(MOGSLib.folders['include_abs'], 'abstractions')
    MOGSLib.folders['schedulers_abs'] = os.path.join(MOGSLib.folders['include_abs'], 'schedulers')
    MOGSLib.folders['contexts_abs'] = os.path.join(MOGSLib.folders['abstractions_abs'], 'contexts')
    MOGSLib.folders['traits_abs'] = os.path.join(MOGSLib.folders['abstractions_abs'], 'traits')
MOGSLib.init()

### Action for consolidating a scheduler data into an intermediary python object ###
class SchedulerAction(argparse.Action):
  def __init__(self, option_strings, dest, nargs=None, **kwargs):
    super(SchedulerAction, self).__init__(option_strings, dest, nargs, **kwargs)
  def __call__(self, parser, namespace, values, option_string=None):
    current = getattr(namespace, self.dest, 2)
    if current is None:
      current = []
    current.append(Scheduler(values.pop(0), values.pop(0)))
    setattr(namespace, self.dest, current)

### Description of parser commands for analyzing external arguments ###
parser = argparse.ArgumentParser(description='Configure MOGSLib to be compiled within a RTS or application.')
parser.add_argument('-traits', metavar='Traits', dest='traits', type=str, help='The solutions traits filename')
parser.add_argument('-sched', '--scheduler', dest='scheds', nargs="+", type=str, action=SchedulerAction, help='Set up a MOGSLib scheduler along with its context')

def resolve_work_snippet(scheds):
  folders = MOGSLib.folders
  file = os.path.join(folders['mogslib_abs'], 'mogslib.h')

  snippets = []
  for i, sched in enumerate(scheds):
    pre_tabs = ''
    if i > 0:
      pre_tabs = '\t\t'
    snippets.append(pre_tabs + 'if(test_scheduler("' + sched[:-2] + '", name))')
    snippets.append('\t\t\treturn do_work<' + str(i) + '>();')


  with open(file, 'r+') as infile:
    filedata = infile.read()
    filedata = filedata.replace('$SCHED_WORK_SNIPPETS$', '\n'.join(snippets))
    infile.seek(0)
    infile.truncate()
    infile.write(filedata)

def resolve_class_names(scheds, contexts, traits):
  folders = MOGSLib.folders
  file = os.path.join(folders['mogslib_abs'], 'mogslib.h')

  with open(file, 'r+') as infile:
    filedata = infile.read()
    filedata = filedata.replace('$TRAITS_CLASS$', traits)
    filedata = filedata.replace('$SCHEDULER_CLASSES$', ', '.join(scheds))
    filedata = filedata.replace('$CONTEXTS_CLASSES$', ', '.join(contexts))
    infile.seek(0)
    infile.truncate()
    infile.write(filedata)

def find_class_name(file):
  folders = MOGSLib.folders
  classname = ''

  with open(file, 'r') as infile:
    p = re.compile('(class|struct)\s+([\w_\d<>]+)\s+.*?\{')
    for line in infile:
      match = p.match(line)
      if match is not None:
        classname = match.group(2)
        break
    if not classname:
      print('Could not detect a class or structure at file ' + file + '.')
      exit()
  return classname

def resolve_includes(scheds, contexts, traits):
  file = os.path.join(MOGSLib.folders['mogslib_abs'], 'mogslib.h')

  unique_scheds = []
  unique_ctx = []

  _scheds = []
  _ctx = []
  _traits = ''

  print("\tSetting MOGSLib schedulers...")
  for sched in scheds:
    if(sched in unique_scheds):
      continue
      unique_scheds.append(sched)
    print("\t\tAdding the " + sched[:-2] + ' scheduler header to mogslib API.')
    _scheds.append('#include <' + MOGSLib.folders['schedulers'] + '/' + sched + '>')

  print("\tSetting MOGSLib contexts...")
  for ctx in contexts:
    if(ctx in unique_ctx):
      continue
    unique_ctx.append(ctx)
    print("\t\tAdding the " + ctx[:-2] + ' context header to mogslib API.')
    _ctx.append('#include <' + MOGSLib.folders['contexts'] + '/' + ctx + '>')

  _traits = '#include <' + MOGSLib.folders['traits'] + '/' + traits + '>\n'
  all_scheds = '\n'.join(_scheds)
  all_ctx = '\n'.join(_ctx)

  with open(file, 'r+') as infile:
    filedata = infile.read()
    filedata = filedata.replace('$TRAITS$', _traits)
    filedata = filedata.replace('$CONTEXTS$', all_ctx)
    filedata = filedata.replace('$SCHEDULERS$', all_scheds)
    infile.seek(0)
    infile.truncate()
    infile.write(filedata)

def setup_mogslib(scheds, traits):
  # Set up the destination file properties
  folders = MOGSLib.folders
  file = os.path.join(folders['mogslib_abs'], 'mogslib.h')

  # declare the top level variables
  sched_includes = []
  context_includes = []
  traits = traits + '.h'

  traits_class = ''
  sched_classes = []
  context_classes = []

  # Test if the traits file exists
  if not os.path.isfile(os.path.join(folders['traits_abs'], traits)):
    print('Traits file \'' + traits + '\' not found in \'' + folders['traits'] + '\'.')
    exit()

  # Check all context and scheduler related filenames.
  for sched in scheds:
    ctx_file = sched.context + '.h'
    sched_file = sched.name + '.h'
    # Test if the filenames exist
    if not os.path.isfile(os.path.join(folders['contexts_abs'], ctx_file)):
      print('Context file \'' + ctx_file + '\' not found in \'' + folders['contexts'] + '\'.')
      exit()
    if not os.path.isfile(os.path.join(folders['schedulers_abs'], sched_file)):
      print('Context file \'' + sched_file + '\' not found in \'' + folders['schedulers'] + '\'.')
      exit()
    # Add the context and scheduler filenames into the list of included files.
    context_includes.append(ctx_file)
    sched_includes.append(sched_file)

  # Copy the mogslib.h stub into the include/mogslib folder.
  shutil.copyfile(os.path.join(folders['stub'], 'mogslib.in.h'), file)
  # Include all needed files into mogslib.h
  resolve_includes(sched_includes, context_includes, traits)

  # Resolve all the classnames of contexts
  print("\tResolving context class names...")
  for ctx in context_includes:
    base_name = find_class_name(os.path.join(folders['contexts_abs'], ctx))
    context_classes.append('Ctx(' + base_name + ')')
  # Resolve all the classnames of schedulers
  print("\tResolving scheduler class names...")
  for i, sched in enumerate(sched_includes):
    base_name = find_class_name(os.path.join(folders['schedulers_abs'], sched))
    sched_classes.append('Sched(' + base_name + ', ' + str(i) + ')')
  # Resolve the classname of the traits structure
  print("\tResolving traits class name...")
  traits_class = find_class_name(os.path.join(folders['traits_abs'], traits))

  # Swap tokens for the classname of the included structures and classes
  print("\tDefining datatypes in MOGSLib API...")
  resolve_class_names(sched_classes, context_classes, traits_class)

  # Swap the WORK_SNIPPETS tokens for calls to the schedulers by name
  print("\tEvoking MOGSLib snippets.")
  resolve_work_snippet(sched_includes)
  print("Done.")

# The actual scripts to run
args = parser.parse_args()
print("Starting the construction of mogslib/mogslib.h")
setup_mogslib(args.scheds, args.traits)