local hello = {}

function hello:Ping(session, subid, is_new, pb_info, name, grade)
    print("abc, ", session, subid, is_new, pb_info, name, grade)
end
print("onload")

return hello
