--Don't Edit It! Auto Generate By Tools
local rpc = require "rpc"
local func_id = require "func_id"

local hello_rpc = {}

function hello_rpc:Ping(session, subid,is_new,pb_info,name,grade)
    print "enter hello rpc"
    rpc.call(session, func_id.FUNC_ID_HELLO_PING, subid,is_new,pb_info,name,grade)
end

function hello_rpc:Pong(session, param0,param1,param2,param3,param4)
    rpc.call(session, func_id.FUNC_ID_HELLO_PONG, param0,param1,param2,param3,param4)
end

return hello_rpc
