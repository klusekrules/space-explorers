local ffi = require("ffi")
ffi.cdef[[
int printf(const char *fmt, ...);
int barfunc(int foo);
void loguj(const char *komunikat );
]]

function f ()
	local bar = ffi.C.barfunc(1)
	ffi.C.printf("Hello %s!\n%d\n", "world", ffi.new("int", bar) )
	ffi.C.loguj("Komunikacja z Loggerem dziala!")
end

function s ()
	ffi.C.loguj("Komunikat stanu")
end

function z ()
	ffi.C.loguj("Komunikat zdarzenia")
end

ffi.C.loguj("Poza funkcj¹")
