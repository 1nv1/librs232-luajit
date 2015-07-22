#!/usr/local/bin/luajit

local ffi = require ("ffi")
local C = ffi.C
local string = require ("string")
local Lib = ffi.load ("./librs232.so.1.0") -- library

ffi.cdef[[
    typedef unsigned int speed_t;
    int serial_open(char *serial_name, speed_t baud);
    int serial_read(int serial_fd, char *data, int size, int timeout_usec);
    void serial_close(int fd);
]]

local lenBuffer = ffi.new ("int", 255)
local baudios = ffi.new("speed_t", 00000013)
local port = ffi.new ("char[?]", 10, "/dev/ttyS0") -- /dev/ttyS0 serial device
local datos = ffi.new ("char[?]", lenBuffer) -- Data buffer
local fd = ffi.new ("int")
local count = ffi.new ("int")
local uSec = ffi.new ("int", 6528*2)

fd = Lib.serial_open (port, baudios)

if fd < 0 then
    print ("Error! Unable to open port")
    os.exit()
end

while true do
    count =  Lib.serial_read (fd, datos, lenBuffer, uSec)
    if count > 0 then
        --print (count)
        print (ffi.string(datos))
    end
end

Lib.serial_close(fd) -- Close the port
