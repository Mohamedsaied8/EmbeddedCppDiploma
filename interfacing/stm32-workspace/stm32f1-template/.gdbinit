add-auto-load-safe-path D:\work\stm32_workspace\stm32f4-template\.gdbinit
define reload
kill
monitor jtag_reset
load
end

target extended localhost:4242
load
