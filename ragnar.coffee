#!/usr/bin/coffee
'use strict'

# REQUIRES ######################################

ragnar = require('bindings')('ragnar.node')

# TEST PHASE
#

console.log ragnar.hello()

#

# RAGNAR APP ####################################

console.log 'It\'s about time ...'
