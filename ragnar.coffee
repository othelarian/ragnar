#!/usr/bin/coffee
'use strict'

# REQUIRES ######################################

ragnar = require('bindings')('ragnar.node')
config = require './config'

# RAGNAR EVENTS #################################

# TODO : set the events listeners
manage_events = (msg) ->
  #
  # onRagnarMsg
  # if config.events.type.hasProperty, do cb
  #
  console.log 'events manager called ?'
  #
  console.log msg
  #

# RAGNAR SPAWN ##################################

# RAGNAR APP ####################################

#status = ragnar.start manage_event

status = ragnar.init()

console.log status

ragnar.events manage_events

#ragnar.systrays manage_

ragnar.start()
