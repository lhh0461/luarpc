local hello_rpc = require "hello_rpc"

local submsg = 111
local is_new = false
local pb = "xxxx"
local name = "test"
local grade = 10

print "abc"

local res = hello_rpc:Ping(0, submsg, is_new, pb, name, grade)
print(res)
