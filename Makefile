# Copyright (c) 2020 Nader G. Zeid
#
# This file is part of GlideJsonVs.
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with GlideJson. If not, see <https://www.gnu.org/licenses/gpl.html>.

C = gcc
COFLAGS = -c -O2 -std=c11 -Wpedantic -Wall -Wextra -Wpointer-arith -Werror=vla -march=native
CC = g++
CC1FLAGS = -std=c++11 -Wpedantic -Wall -Wextra -Wpointer-arith -Werror=vla -march=native
CC2FLAGS = -c -O2 -I. \
-I./GlideJson/glidejson-1.0.0/include/glidejson \
-I./json-for-modern-cpp/json-3.9.1/include \
-I./jsoncpp/jsoncpp-1.9.4/include/ \
-I./cjson/cJSON-1.7.14 \
-I./rapidjson/rapidjson-1.1.0/include/rapidjson
CCOFLAGS = $(CC2FLAGS) $(CC1FLAGS)

GLIDE_JSON_VS = GlideJsonVs
GLIDE_JSON_VS_SOURCES_CPP = GlideJsonVs.cpp GlideJson/glidejson-1.0.0/src/glidejson/GlideJson.cpp $(wildcard jsoncpp/jsoncpp-1.9.4/src/lib_json/*.cpp)
GLIDE_JSON_VS_SOURCES_C = cjson/cJSON-1.7.14/cJSON.c
GLIDE_JSON_VS_OBJECTS_CPP = $(GLIDE_JSON_VS_SOURCES_CPP:.cpp=.o)
GLIDE_JSON_VS_OBJECTS_C = $(GLIDE_JSON_VS_SOURCES_C:.c=.o)
GLIDE_JSON_VS_OBJECTS = $(GLIDE_JSON_VS_SOURCES_CPP:.cpp=.o) $(GLIDE_JSON_VS_SOURCES_C:.c=.o)
GLIDE_JSON_VS_OBJECT_FILES = $(notdir $(GLIDE_JSON_VS_OBJECTS))

.PHONY: all clean distclean

all: $(GLIDE_JSON_VS)

clean:
	rm -vf $(GLIDE_JSON_VS) $(GLIDE_JSON_VS_OBJECT_FILES)

distclean: clean

$(GLIDE_JSON_VS_OBJECTS_CPP): %.o: %.cpp
	$(CC) $(CCOFLAGS) -o $(@F) $<

$(GLIDE_JSON_VS_OBJECTS_C): %.o: %.c
	$(C) $(COFLAGS) -o $(@F) $<

$(GLIDE_JSON_VS): $(GLIDE_JSON_VS_OBJECTS_CPP) $(GLIDE_JSON_VS_OBJECTS_C)
	$(CC) $(CC1FLAGS) -o $(GLIDE_JSON_VS) $(GLIDE_JSON_VS_OBJECT_FILES)
