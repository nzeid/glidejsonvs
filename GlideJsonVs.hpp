// Copyright (c) 2021 Nader G. Zeid
//
// This file is part of GlideJsonVs.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with GlideJson. If not, see <https://www.gnu.org/licenses/gpl.html>.

#ifndef GLIDE_JSON_VS_HPP
#define GLIDE_JSON_VS_HPP

#include "GlideJson.hpp"
#include "nlohmann/json.hpp"
#include "json/json.h"
#include "cJSON.h"
#include "document.h"
#include "writer.h"
#include "stringbuffer.h"

#include <vector>
#include <string>
#include <ctime>
#include <chrono>
#include <iostream>
#include <random>
#include <thread>

class GlideJsonVs {
  private:
    static std::vector<std::string> errors;
  public:
    static void escapeByte(const unsigned char &input, std::string &output);
    static void generateJson(const int &mode, std::string * const &output, std::string * const &outputWithWs);
    static std::string generateJson(const int &mode);
    static std::pair<std::string, std::string> generateJsonWithWs();
    static void testJson();
    static int run();
};

#endif
