-- Simple script for testing porpuses of "librs232-luajit"
local rs232 = require("mod_librs232")
port = rs232.new()
-- Arguments:
-- 	Device name, Baud rate, Timeout in micro-seconds
port:open("/dev/ttyUSB0", 115200, 10000)
count, data = port:read()
print(data)
port:close()
