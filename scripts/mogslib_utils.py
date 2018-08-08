#!/usr/bin/python3

import os
import shutil

### Scheduler class that contains all the data needed to express a scheduler in MOGSLib ###
class Scheduler:
  def __init__(self, name, concepts):
    self.name = name
    self.concepts = concepts

### Function to get most of the important folders paths in MOGSLib ###
def get_folder_map():
  folder_map = {'include': os.path.join(os.path.dirname(os.path.dirname(os.path.realpath(__file__))), 'include')}
  folder_map['system'] = os.path.join(folder_map['include'], 'system')
  folder_map['stub'] = os.path.join(os.path.dirname(os.path.realpath(__file__)), 'stubs')
  folder_map['mogslib'] = os.path.join(folder_map['include'], 'mogslib')
  folder_map['rts'] = os.path.join(folder_map['include'], 'rts')
  folder_map['binders'] = os.path.join(folder_map['include'], 'binders')
  folder_map['concepts'] = os.path.join(folder_map['include'], 'concepts')
  folder_map['initializers'] = os.path.join(folder_map['concepts'], 'initializer')
  folder_map['schedulers'] = os.path.join(folder_map['include'], 'schedulers')

  return folder_map