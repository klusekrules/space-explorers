local ffi = require("ffi")
ffi.cdef[[
int printf(const char *fmt, ...);
int barfunc(int foo);
]]
local bar = ffi.C.barfunc(1)
ffi.C.printf("Hello %s!\n%d\n", "world", ffi.new("int", bar) )