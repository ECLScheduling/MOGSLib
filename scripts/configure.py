#!/usr/bin/python3

import argparse
from support.mogslib_utils import Scheduler

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

### Declaration of the RTS configuration functions ###
from support.rts_configuration import *

### Declaration of the Scheduler configuration functions ###
from support.sched_configuration import *


generate_defs_for_rts(args.rts)
configure_schedulers(args.scheds, args.rts)