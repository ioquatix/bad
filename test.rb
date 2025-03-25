#!/usr/bin/env ruby

$LOAD_PATH.unshift(File.expand_path("../ext", __dir__))

require_relative 'lib/bad'
require 'objspace'

TracePoint.new(:c_return) do |trace_point|
	GC.verify_internal_consistency
end.enable

# Promote the object to old generation
object = Bad::Object.new("safe")
10.times { GC.start }

object.value = {value: "Hello, World!"}
