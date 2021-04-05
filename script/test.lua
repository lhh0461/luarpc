local hello_rpc = require "hello_rpc"

local iv = 10
local cv = "abc"
local tv = {1:2,"a":1}
local res = hello_rpc:Ping(mailbox, iv, cv, tc)
print(res)