CXX=g++
CXXFLAGS=-O2 -std=c++11 -fno-builtin-memcmp -msse -msse4.2

.PHONY: clean all

all: ROCKSDB strings_example hashes_example sets_example

# Get processor numbers
dummy := $(shell ("$(CURDIR)/../detect_environment" "$(CURDIR)/make_config.mk"))
include make_config.mk
LDFLAGS = -lpthread -lrt $(ROCKSDB_LDFLAGS)

ifndef STORAGE_PATH
  $(warning Warning: missing storage path, using default)
  STORAGE_PATH=..
endif
STORAGE_INCLUDE_DIR=$(STORAGE_PATH)/include
STORAGE_LIBRARY=$(STORAGE_PATH)/lib/libstorage.a

ifndef ROCKSDB_PATH
  $(warning Warning: missing rocksdb path, using default)
	ROCKSDB_PATH=../deps/rocksdb
endif
ROCKSDB_INCLUDE_DIR=$(ROCKSDB_PATH)/include
ROCKSDB_LIBRARY=$(ROCKSDB_PATH)/librocksdb.a

ifndef SLASH_PATH
  $(warning Warning: missing slash path, using default)
	SLASH_PATH=../deps/slash
endif
SLASH_INCLUDE_DIR=$(SLASH_PATH)
SLASH_LIBRARY=$(SLASH_PATH)/slash/lib/libslash.a

CXXFLAGS+= -I$(STORAGE_INCLUDE_DIR) -I$(ROCKSDB_INCLUDE_DIR) -I$(SLASH_INCLUDE_DIR)

DEP_LIBS = $(STORAGE_LIBRARY) $(ROCKSDB_LIBRARY) $(SLASH_LIBRARY)
LDFLAGS := $(DEP_LIBS) $(LDFLAGS)

ROCKSDB:
	$(AM_V_at)make -j $(PROCESSOR_NUMS) -C $(ROCKSDB_PATH)/ static_lib

SLASH:
	$(AM_V_at)make -C $(SLASH_PATH)/slash

strings_example: strings_example.cc
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

hashes_example: hashes_example.cc
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

sets_example: sets_example.cc
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

clean:
	find . -name "*.[oda]" -exec rm -f {} \;
	rm -f ./make_config.mk
	rm -rf ./strings_example ./hashes_example ./sets_example
