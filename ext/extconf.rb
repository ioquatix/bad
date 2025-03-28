#!/usr/bin/env ruby

require "mkmf"

gem_name = "bad"
extension_name = "bad"

create_makefile("#{gem_name}/#{extension_name}", extension_name)
