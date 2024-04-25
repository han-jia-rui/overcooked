.DEFAULT_GOAL := all
TOKEN ?= submit
SHELL := /bin/bash

all:
	@if [[ ! -e build/Makefile ]]; then \
		mkdir -p build; \
		cd build && cmake .. -DCMAKE_BUILD_TYPE=Debug; fi
	@make -C build
	@if [[ ! -e build-win/Makefile ]]; then \
		mkdir -p build-win; \
		cd build-win && cmake .. -DCMAKE_BUILD_TYPE=Debug -DFOR_WIN=ON; fi
	@make -C build-win

clean:
	@if [[ -d build ]]; then \
		rm -r build; fi
	@if [[ -d build-win ]]; then \
		rm -r build-win; fi

submit:
	$(eval TEMP := $(shell mktemp -d))
	$(eval BASE := $(shell basename $(CURDIR)))
	$(eval FILE := ${TEMP}/${TOKEN}.zip)
	@cd .. && zip -qr ${FILE} ${BASE}/.git
	@echo "Created submission archive ${FILE}"
	@curl -m 5 -w "\n" -X POST -F "TOKEN=${TOKEN}" -F "FILE=@${FILE}" \
		https://exam.problemsolving.top:8085/api/v2/submission/lab
	@rm -r ${TEMP}

