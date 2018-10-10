#!/usr/bin/python3

import os
import shutil

### Scheduler class that contains all the data needed to express a scheduler in MOGSLib ###
class Scheduler:
  def __init__(self, name, concepts):
    self.name = name
    self.concepts = concepts

class MOGSLib:
  folders = dict()

  def init():
    MOGSLib.folders = {'include': os.path.join(os.path.dirname(os.path.dirname(os.path.realpath(__file__))), 'include')}
    MOGSLib.folders['system'] = os.path.join(MOGSLib.folders['include'], 'system')
    MOGSLib.folders['stub'] = os.path.join(os.path.dirname(os.path.realpath(__file__)), 'stubs')
    MOGSLib.folders['mogslib'] = os.path.join(MOGSLib.folders['include'], 'mogslib')
    MOGSLib.folders['rts'] = os.path.join(MOGSLib.folders['include'], 'rts')
    MOGSLib.folders['binders'] = os.path.join(MOGSLib.folders['include'], 'binders')
    MOGSLib.folders['concepts'] = os.path.join(MOGSLib.folders['include'], 'concepts')
    MOGSLib.folders['initializers'] = os.path.join(MOGSLib.folders['concepts'], 'initializer')
    MOGSLib.folders['schedulers'] = os.path.join(MOGSLib.folders['include'], 'schedulers')

MOGSLib.init()