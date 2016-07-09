local rs232 = {}

local RS232 = {}

function RS232:open(port_name, baud_rate, timeout_usec)
	local name = self.ffi.new ("char[?]", 20, port_name) -- /dev/ttyS0 serial device
	self.port.librs232_init(self.dev, name, timeout_usec)
	if self.port.librs232_open(self.dev, baud_rate) < 0 then
    return false
	end
	return true
end 

function RS232:read()
	count =  self.port.librs232_read(self.dev, self.datos, self.lenBuffer)
	self.datos[count] = 0
	return count, self.ffi.string(self.datos)
end

function RS232:write(data, length)
	return self.port.librs232_write(self.dev, self.datos, length);
end

function RS232:close() -- Close the port
	self.port.librs232_close(self.dev)
end


function rs232.new()
	local self = {}
  setmetatable(self, { __index = RS232 })
	
	local ffi = require ("ffi")
	local C = ffi.C
	local string = require ("string")
	self.port = ffi.load ("./librs232.so.1.0") -- library

	ffi.cdef[[
		typedef unsigned int speed_t;
		typedef struct __DEV_RS232 {
			int connect;
			char name[50];
			speed_t baud;
			int fd;
			int timeout;
		} DEV_RS232;
		void librs232_init(DEV_RS232* dev, char* name, int timeout);
		int librs232_open(DEV_RS232* dev, speed_t baud);
		int librs232_read(DEV_RS232* dev, char *data, int size);
		int librs232_write(DEV_RS232* dev, char *data, int size);
		void librs232_close(DEV_RS232* dev);
	]]

	lenBuffer = ffi.new ("int", 1024)
	self.datos = ffi.new ("char[?]", lenBuffer) -- Data buffer
	self.dev = ffi.new("DEV_RS232[1]")
  self.lenBuffer = lenBuffer
  self.ffi = ffi
  return self
end

return rs232
