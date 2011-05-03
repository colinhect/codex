@echo off

S:/Projects/codex/bin/codexc.exe %1 -o temp.cxe
S:/Projects/codex/bin/codex.exe temp.cxe
del temp.cxe
pause


