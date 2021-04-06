PROJECT=server

CXX=g++
CXXFLAGS=-W -std=c++11 -g -ldl

SRC_DIR:=src
INC_DIR:=include
LUA_CLIB_DIR:=luaclib
THIRD_PART_DIR:=3rd
PROTO_DIR:=$(THIRD_PART_DIR)/protobuf
LUA_DIR:=$(THIRD_PART_DIR)/lua-5.3.5/install

INC_FILES:=-I$(INC_DIR) \
	-I$(LUA_DIR)/include \

CXX_SRC_FILES:=$(foreach v, $(SRC_DIR), $(wildcard $(v)/*.cpp))

CXX_OBJ_FILES:=$(subst .cpp,.o,$(CXX_SRC_FILES))

LIBS=-L$(LUA_DIR)/lib

STATIC_LIBS= -llua 

all:$(CXX_OBJ_FILES) $(LUA_LIB)
	$(CXX) $(CXXFLAGS) $(CXX_OBJ_FILES) -o $(PROJECT) $(LIBS) $(STATIC_LIBS)

$(SRC_DIR)/%.o:$(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) $< -c -o $@ $(INC_FILES) $(LIBS)

.PHONY:clean rpc
clean:
	-rm -f $(PROJECT)
	-rm -rf $(SRC_DIR)/*.o
rpc:
	@python tools/parse_rpc.py
