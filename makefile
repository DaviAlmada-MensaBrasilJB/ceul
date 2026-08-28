build_dir = build
source = src
start_file = main.c
end_file = main.exe

linux_end_file = main
user = DILSON SOUZA

.PHONY: all ccr compile run clean alll ccrl compilel runl cleanl deploy commit push add depsource

# ---------------- Windows ----------------

all: compile run

ccr: clean compile run

compile:
	@if not exist $(build_dir) mkdir $(build_dir)
	gcc ./$(source)/$(start_file) -o ./$(build_dir)/windows/$(end_file)

run:
	$(build_dir)\windows\$(end_file)

clean:
	@if exist $(build_dir)\windows\$(end_file) del /Q "$(build_dir)\windows\$(end_file)"


# ---------------- Linux / WSL ----------------

alll: compilel runl

ccrl: cleanl compilel runl

compilel:
	wsl bash -lc "cd \"/mnt/c/Users/$(user)/Desktop/CEUL\" && mkdir -p $(build_dir) && gcc ./$(source)/$(start_file) -o ./$(build_dir)/linux/$(linux_end_file)"

runl:
	wsl bash -lc "cd \"/mnt/c/Users/$(user)/Desktop/CEUL\" && ./$(build_dir)/linux/$(linux_end_file)"

cleanl:
	wsl bash -lc "cd \"/mnt/c/Users/$(user)/Desktop/CEUL\" && rm -f ./$(build_dir)/linux/$(linux_end_file)"

# ---------------- GIT / Deployment ----------------

DATE_HOUR := $(shell powershell -Command "Get-Date -Format 'dd/MM/yyyy - HH:mm'")
M ?= AUTO: Commit deploy at $(DATE_HOUR) (DD/MM/YYYY - 24h Format) UTC-3
A ?= .
deploy: clean cleanl compile compilel add commit push
depsource: add commit push

add:
	git add $(A)

commit:
	git commit -m "$(M)"

push:
	git push