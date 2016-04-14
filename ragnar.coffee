#!/usr/bin/coffee
'use strict'

# REQUIRES ######################################

ragnar = require('bindings')('ragnar.node')

# RAGNAR APP ####################################

status = ragnar.start()

console.log status

#
