.PHONY: all clean run test play submit
.DEFAULT_GOAL := all
TOKEN ?= submit
SHELL := /bin/bash
LEVEL ?= 1
MAP ?= 1


all:
	# @if [[ ! -e build/Makefile ]]; then \
	# 	mkdir -p build; \
	# 	cd build && cmake .. -DCMAKE_BUILD_TYPE=Debug -DFOR_WIN=OFF; fi
	# @make -C build
	@if [[ ! -e build-win/Makefile ]]; then \
		mkdir -p build-win; \
		cd build-win && cmake .. -DCMAKE_BUILD_TYPE=Debug -DFOR_WIN=ON; fi
	@make -C build-win

clean:
	@if [[ -d build ]]; then \
		rm -r build; fi
	@if [[ -d build-win ]]; then \
		rm -r build-win; fi

run: all
	@cd ../QtOvercooked && wine QtOvercooked.exe -p ../overcooked-2022/build-win/main-win.exe -l $(shell find ../overcooked-2022/maps -name "level${LEVEL}-${MAP}.txt")

test: all
	@cd ../QtOvercooked && wine runner.exe -p ../overcooked-2022/build-win/main-win.exe -l $(shell find ../overcooked-2022/maps -name "level${LEVEL}-${MAP}.txt")

test-linux: all
	@cd ../QtOvercooked && ./runner -p ../overcooked-2022/build/main -l $(shell find ../overcooked-2022/maps -name "level${LEVEL}-${MAP}.txt")

play:
	@cd ../QtOvercooked && wine QtOvercooked.exe -l $(shell find ../overcooked-2022/maps -name "level${LEVEL}-${MAP}.txt")

submit:
	$(eval TEMP := $(shell mktemp -d))
	$(eval BASE := $(shell basename $(CURDIR)))
	$(eval FILE := ${TEMP}/${TOKEN}.zip)
	@cd .. && zip -qr ${FILE} ${BASE}/.git
	@echo "Created submission archive ${FILE}"
	@curl -k -m 5 -w "\n" -X POST -F "TOKEN=${TOKEN}" -F "FILE=@${FILE}" \
		https://oj.njups.top/api/v2/submission/lab
	@rm -r ${TEMP}

