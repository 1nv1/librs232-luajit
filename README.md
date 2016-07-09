librs232-luajit
===============

Library for access to RS232 serial port from LuaJIT on GNU/Linux.

The complete library has two part, one it's the library written in C and
other is the Lua module.

Test
====

```lua
	local rs232 = require("mod_librs232")
	port = rs232.new()
	port:open("/dev/ttyUSB0", 115200, 10000)
	count, data = port:read()
	print(data)
	port:close()
```

