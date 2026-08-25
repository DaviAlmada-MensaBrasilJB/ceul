build_dir = build
source = src
start_file = main.c
end_file = main.exe

linux_end_file = main

.PHONY: all ccr compile run clean alll ccrl compilel runl cleanl

# ---------------- Windows ----------------

all: compile run

ccr: clean compile run

compile:
	@if not exist $(build_dir) mkdir $(build_dir)
	gcc ./$(source)/$(start_file) -o ./$(build_dir)/$(end_file)

run:
	$(build_dir)\$(end_file)

clean:
	@if exist $(build_dir)\$(end_file) del /Q "$(build_dir)\$(end_file)"


# ---------------- Linux / WSL ----------------

alll: compilel runl

ccrl: cleanl compilel runl

compilel:
	wsl bash -lc "cd /mnt/c/Users/'DILSON SOUZA'/Desktop/CEUL && mkdir -p $(build_dir) && gcc ./$(source)/$(start_file) -o ./$(build_dir)/$(linux_end_file)"

runl:
	wsl bash -lc "cd /mnt/c/Users/'DILSON SOUZA'/Desktop/CEUL && ./$(build_dir)/$(linux_end_file)"

cleanl:
	wsl bash -lc "cd /mnt/c/Users/'DILSON SOUZA'/Desktop/CEUL && rm -f ./$(build_dir)/$(linux_end_file)"