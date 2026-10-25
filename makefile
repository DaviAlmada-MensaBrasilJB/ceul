final_dir ?= final
build_dir = build/$(final_dir)


source = src
start_file = main.c
C ?= 0-0-3
end_file = ceul_repl_$(C)_windows-x86_64.exe

linux_end_file = ceul_repl_$(C)_linux-x86_64
macos_end_file = ceul_repl_$(C)_darwin_macos-x86_64
user = DILSON SOUZA

gmode = normal

ifeq ($(gmode), pedantic)
	FLAGS = -Wall -Wextra -Wpedantic
else
	ifeq ($(gmode), all)
		FLAGS = -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion
	else
		FLAGS =
	endif
endif

.PHONY: all ccr compile run clean alll ccrl compilel runl cleanl deploy commit push add depsource allm ccrm compilem runm cleanm

# ---------------- Windows ----------------

all: compile run

ccr: clean compile run

V ?= gnu23
# Hello from WSL2 Ubuntu NeoVim!
compile:
	@if not exist $(build_dir) mkdir $(build_dir)
	gcc -std=$(V) -m64 ./$(source)/$(start_file) $(FLAGS) -o ./$(build_dir)/$(end_file)

run:
	$(build_dir)\$(end_file)

clean:
	@if exist $(build_dir)\$(end_file) del /Q "$(build_dir)\$(end_file)"


# ---------------- Linux / WSL ----------------

alll: compilel runl

ccrl: cleanl compilel runl

compilel:
	wsl bash -lc "cd \"/mnt/c/Users/$(user)/Desktop/CEUL\" && mkdir -p $(build_dir) && gcc -std=$(V) -m64 ./$(source)/$(start_file) -o ./$(build_dir)/$(linux_end_file)"

runl:
	wsl bash -lc "cd \"/mnt/c/Users/$(user)/Desktop/CEUL\" && ./$(build_dir)/$(linux_end_file)"

cleanl:
# 	wsl bash -lc "cd \"/mnt/c/Users/$(user)/Desktop/CEUL\" && rm -f ./$(build_dir)/linux/$(linux_end_file)"
	@if exist $(build_dir)\$(linux_end_file) del /Q "$(build_dir)\$(linux_end_file)"

# ---------------- MacOS ----------------

allm: compilem runm

ccrm: cleanm compilem runm

compilem:
	x86_64-apple-darwin-gcc -std=$(V) -m64 ./$(source)/$(start_file) $(FLAGS) -o ./$(build_dir)/$(macos_end_file)

runm:
	$(build_dir)\$(macos_end_file)

cleanm:
	@if exist $(build_dir)\$(macos_end_file) del /Q "$(build_dir)\$(macos_end_file)"

# ---------------- GIT / Deployment ----------------

DATE_HOUR := $(shell powershell -Command "Get-Date -Format 'dd/MM/yyyy - HH:mm'")
M ?= AUTO: Commit deploy at $(DATE_HOUR) (DD/MM/YYYY - 24h Format) UTC-3
A ?= .
deploy: clean cleanl cleanm compile compilel compilem add commit push
depsource: add commit push

add:
	git add $(A)

commit:
	git commit -m "$(M)"

push:
	git push