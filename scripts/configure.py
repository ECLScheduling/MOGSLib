#!/usr/bin/python3

import argparse

### Scheduler class that contains all the data needed to express a scheduler in MOGSLib ###
class Scheduler:
  def __init__(self, name, concepts):
    self.name = name
    self.concepts = concepts

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
parser = argparse.ArgumentParser(description='Configure MOGSLib to be compiled within a RTS or application.')
parser.add_argument('-rts', metavar='RTS', type=str, help='MOGSLib target RTS')
parser.add_argument('-sched', '--scheduler', dest='scheds', nargs="+", type=str, action=SchedulerAction, help='Set up a MOGSLib scheduler along with its concepts')

args = parser.parse_args()

### Declaration of the RTS to lambda map ###
from rts_configuration import *

generate_defs_for_rts(args.rts)

###