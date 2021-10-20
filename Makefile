SHELL := $(shell which bash)

PROJECT_ROOT = $(shell pwd)
TEST_SQL_DIRECTORIES = $(shell pwd)/test/sql

TEST_SQL_FILES = $(shell find $(TEST_SQL_DIRECTORIES) -name "*.sql")

SERVER_BIN := $(PROJECT_ROOT)/build/bin/observer
CLIENT_BIN := $(PROJECT_ROOT)/build/bin/obclient

default: build

build: init-submodule libevent googletest jsoncpp parser miniob

init-submodule:
	@git submodule update --init --recursive

libevent:
	@cd $(PROJECT_ROOT)/deps/libevent && \
		git checkout release-2.1.12-stable && \
		mkdir -p build && cd build && \
		cmake .. -DEVENT__DISABLE_OPENSSL=ON && make && sudo make install

googletest:
	@cd $(PROJECT_ROOT)/deps/googletest && \
		mkdir -p build && cd build && \
		cmake .. && make && sudo make install

jsoncpp:
	@cd $(PROJECT_ROOT)/deps/jsoncpp && \
		mkdir -p build && cd build  && \
		cmake -DJSONCPP_WITH_TESTS=OFF -DJSONCPP_WITH_POST_BUILD_UNITTEST=OFF ..  && \
		make && sudo make install

parser:
	cd $(PROJECT_ROOT)/src/observer/sql/parser && \
		lex lex_sql.l && bison -d -v yacc_sql.y && rm -rf yacc_sql.output

miniob:
	mkdir -p build && cd build  && \
		cmake .. && make

clean:
	rm -rf $(PROJECT_ROOT)/build
	rm -rf $(PROJECT_ROOT)/deps/jsoncpp/build
	rm -rf $(PROJECT_ROOT)/deps/googletest/build
	rm -rf $(PROJECT_ROOT)/deps/libevent/build

clean-storage:
	rm -rf $(PROJECT_ROOT)/build/miniob

run-server:
	@if [ ! -f "$(SERVER_BIN)" ]; then \
		make build; \
	fi
	cd $(PROJECT_ROOT)/build && $(SERVER_BIN)

run-client:
	@if [ ! -f "$(CLIENT_BIN)" ]; then \
		make build; \
	fi
	$(CLIENT_BIN)

sql-test:
	@echo "Start to test all SQL files..."
	@for sql_file in $(TEST_SQL_FILES); do \
		$(CLIENT_BIN) < $$sql_file | tr -d '\r' > $$sql_file.tmp.res && \
		(diff $$sql_file.tmp.res $$sql_file.res > /dev/null && echo "Test $$sql_file PASSED") || \
		echo "Test $$sql_file FAILED"; rm -rf $$sql_file.tmp.res; \
	done
