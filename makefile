build_dir = build
source = src
start_file = main.c
end_file = main.exe

.PHONY: all ccr compile run clean

all: compile run

ccr: clean compile run

compile:
	@if not exist $(build_dir) mkdir $(build_dir)
	gcc ./$(source)/$(start_file) -o ./$(build_dir)/$(end_file)

run:
	$(build_dir)\$(end_file)

clean:
	@if exist $(build_dir)\$(end_file) del /Q "$(build_dir)\$(end_file)"