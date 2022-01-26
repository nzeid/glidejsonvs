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

#include "GlideJsonVs.hpp"

std::vector<std::string> GlideJsonVs::errors;

void GlideJsonVs::escapeByte(const unsigned char &input, std::string &output) {
  if(input < 32 || input == '"' || input == '\\' || input > 127) {
    switch(input) {
      case '"':
      case '\\':
        output.push_back('\\');
        output.push_back(input);
        break;
      case '\b':
        output.push_back('\\');
        output.push_back('b');
        break;
      case '\f':
        output.push_back('\\');
        output.push_back('f');
        break;
      case '\n':
        output.push_back('\\');
        output.push_back('n');
        break;
      case '\r':
        output.push_back('\\');
        output.push_back('r');
        break;
      case '\t':
        output.push_back('\\');
        output.push_back('t');
        break;
      default:
        output.append("\\u00");
        output.push_back(GlideJson::getHex(input >> 4));
        output.push_back(GlideJson::getHex(input & 15));
    }
  }
  else {
    output.push_back(input);
  }
}

void GlideJsonVs::generateJson(const int &mode, std::string * const &output, std::string * const &outputWithWs) {
  switch(mode) {
    case 0:
      *output = "null";
      if(outputWithWs) {
        *outputWithWs = *output;
      }
      break;
    case 1:
      *output = "false";
      if(outputWithWs) {
        *outputWithWs = *output;
      }
      break;
    case 2:
      *output = "true";
      if(outputWithWs) {
        *outputWithWs = *output;
      }
      break;
    case 3:
      output->clear();
      if(std::rand() & 1) {
        *output += "-";
      }
      *output += std::to_string(std::rand() % 10000);
      if(std::rand() & 1) {
        *output += ".";
        if(std::rand() & 1) {
          *output += "0";
        }
        *output += std::to_string(std::rand() % 10000);
      }
      if(std::rand() & 1) {
        *output += ((std::rand() & 1) ? "E" : "e");
        if(std::rand() & 1) {
          *output += ((std::rand() & 1) ? "+" : "-");
        }
        if(std::rand() & 1) {
          *output += "0";
        }
        *output += std::to_string(std::rand() % 100);
      }
      if(outputWithWs) {
        *outputWithWs = *output;
      }
      break;
    case 4:
      *output = '"';
      {
        /*
          Grammar for UTF-8 from RFC 3629:

          UTF8-octets = *( UTF8-char )
          UTF8-char   = UTF8-1 / UTF8-2 / UTF8-3 / UTF8-4
          UTF8-1      = %x00-7F
          UTF8-2      = %xC2-DF UTF8-tail
          UTF8-3      = %xE0 %xA0-BF UTF8-tail /
                        %xE1-EC 2( UTF8-tail ) /
                        %xED %x80-9F UTF8-tail /
                        %xEE-EF 2( UTF8-tail )
          UTF8-4      = %xF0 %x90-BF 2( UTF8-tail ) /
                        %xF1-F3 3( UTF8-tail ) /
                        %xF4 %x80-8F 2( UTF8-tail )
          UTF8-tail   = %x80-BF
        */
        unsigned char cChar;
        size_t length(std::rand() % 250);
        while(length) {
          cChar = std::rand() % 244 + 1;
          if(cChar >= 128 && cChar <= 193) {
          }
          else if(cChar >= 194 && cChar <= 223) {
            output->push_back(cChar);
            output->push_back(128 + (std::rand() % 64));
          }
          else if((cChar >= 224 && cChar <= 236) || (cChar >= 238 && cChar <= 239)) {
            output->push_back(cChar);
            output->push_back(160 + (std::rand() % 32));
            output->push_back(128 + (std::rand() % 64));
          }
          else if(cChar == 237) {
            output->push_back(cChar);
            output->push_back(128 + (std::rand() % 32));
            output->push_back(128 + (std::rand() % 64));
          }
          else if(cChar == 240) {
            output->push_back(cChar);
            output->push_back(144 + (std::rand() % 48));
            output->push_back(128 + (std::rand() % 64));
            output->push_back(128 + (std::rand() % 64));
          }
          else if(cChar >= 241 && cChar <= 243) {
            output->push_back(cChar);
            output->push_back(128 + (std::rand() % 64));
            output->push_back(128 + (std::rand() % 64));
            output->push_back(128 + (std::rand() % 64));
          }
          else if(cChar == 244) {
            output->push_back(cChar);
            output->push_back(128 + (std::rand() % 16));
            output->push_back(128 + (std::rand() % 64));
            output->push_back(128 + (std::rand() % 64));
          }
          else {
            GlideJsonVs::escapeByte(cChar, *output);
          }
          --length;
        }
      }
      output->push_back('"');
      if(outputWithWs) {
        *outputWithWs = *output;
      }
      break;
    case 5:
      *output = '[';
      if(outputWithWs) {
        *outputWithWs = '[';
      }
      {
        size_t length((std::rand() & 1) * (1 + std::rand() % 10));
        if(length) {
          do {
            std::string nested;
            if(outputWithWs) {
              std::string nestedWithWs;
              GlideJsonVs::generateJson(std::rand() % 7, &nested, &nestedWithWs);
              *outputWithWs += nestedWithWs;
              *outputWithWs += ',';
            }
            else {
              GlideJsonVs::generateJson(std::rand() % 7, &nested, NULL);
            }
            *output += nested;
            *output += ',';
          }
          while(--length);
          (*output)[output->size() - 1] = ']';
          if(outputWithWs) {
            (*outputWithWs)[outputWithWs->size() - 1] = ']';
          }
        }
        else {
          *output += ']';
          if(outputWithWs) {
            *outputWithWs += ']';
          }
        }
      }
      break;
    case 6:
      *output = '{';
      if(outputWithWs) {
        *outputWithWs = '{';
      }
      {
        std::string cKey;
        std::map<std::string, bool> knownKeys;
        size_t length((std::rand() & 1) * (1 + std::rand() % 10));
        if(length) {
          do {
            if(outputWithWs) {
              std::string cKeyWithWs;
              do {
                GlideJsonVs::generateJson(4, &cKey, &cKeyWithWs);
              }
              while(knownKeys.count(cKey));
              *output += cKey;
              *outputWithWs += cKeyWithWs;
              knownKeys[std::move(cKey)] = true;
              *output += ':';
              *outputWithWs += ':';
              GlideJsonVs::generateJson(std::rand() % 7, &cKey, &cKeyWithWs);
              *output += cKey;
              *output += ',';
              *outputWithWs += cKeyWithWs;
              *outputWithWs += ',';
            }
            else {
              do {
                GlideJsonVs::generateJson(4, &cKey, NULL);
              }
              while(knownKeys.count(cKey));
              *output += cKey;
              knownKeys[std::move(cKey)] = true;
              *output += ':';
              GlideJsonVs::generateJson(std::rand() % 7, &cKey, NULL);
              *output += cKey;
              *output += ',';
            }
          }
          while(--length);
          (*output)[output->size() - 1] = '}';
          if(outputWithWs) {
            (*outputWithWs)[outputWithWs->size() - 1] = '}';
          }
        }
        else {
          *output += '}';
          if(outputWithWs) {
            *outputWithWs += '}';
          }
        }
      }
      break;
    default:
      abort();
  }
  if(outputWithWs) {
    size_t length(std::rand() % 6);
    if(length) {
      unsigned char whitespace;
      do {
        whitespace = std::rand() % 8;
        switch(whitespace) {
          case 0:
            *outputWithWs += '\t';
            break;
          case 1:
            outputWithWs->insert(0, 1, '\t');
            break;
          case 2:
            *outputWithWs += '\n';
            break;
          case 3:
            outputWithWs->insert(0, 1, '\n');
            break;
          case 4:
            *outputWithWs += '\r';
            break;
          case 5:
            outputWithWs->insert(0, 1, '\r');
            break;
          case 6:
            *outputWithWs += ' ';
            break;
          case 7:
            outputWithWs->insert(0, 1, ' ');
            break;
          default:
            abort();
        }
      }
      while(--length);
    }
  }
}

std::string GlideJsonVs::generateJson(const int &mode) {
  std::string output;
  GlideJsonVs::generateJson(mode, &output, NULL);
  return output;
}

std::pair<std::string, std::string> GlideJsonVs::generateJsonWithWs() {
  std::pair<std::string, std::string> output;
  GlideJsonVs::generateJson(std::rand() % 7, &(output.first), &(output.second));
  return output;
}

void GlideJsonVs::testJson() {
  std::pair<std::string, std::string> generated;
  std::string testEncoded;
  auto start(std::chrono::steady_clock::now());
  //
  GlideJson testGlideJson;
  nlohmann::json testJfmc;
  Json::Value testJsonCpp;
  rapidjson::Document testRapidJson;
  decltype(start - start) timerPGlideJson(0);
  auto timerEGlideJson(timerPGlideJson);
  auto timerPJfmc(timerPGlideJson);
  auto timerEJfmc(timerPGlideJson);
  auto timerPJsonCpp(timerPGlideJson);
  auto timerEJsonCpp(timerPGlideJson);
  auto timerPCJson(timerPGlideJson);
  auto timerECJson(timerPGlideJson);
  auto timerPRapidJson(timerPGlideJson);
  auto timerERapidJson(timerPGlideJson);
  // Warmup:
  testGlideJson = GlideJson::parse("{}");
  testEncoded = testGlideJson.toJson();
  //
  testJfmc = nlohmann::json::parse("{}");
  testEncoded = testJfmc.dump();
  //
  std::stringstream testInJsonCpp("{}");
  std::stringstream testOutJsonCpp;
  testInJsonCpp >> testJsonCpp;
  testOutJsonCpp << testJsonCpp;
  //
  const char * cGenerated;
  size_t cGeneratedSize;
  cJSON *cJsonTest(cJSON_ParseWithLength("{}", 2));
  char *cTestEncoded = cJSON_Print(cJsonTest);
  cJSON_Delete(cJsonTest);
  free(cTestEncoded);
  //
  const char *ccTestEncoded;
  testRapidJson.Parse("{}");
  {
    rapidjson::StringBuffer rapidJsonBuffer;
    rapidjson::Writer<rapidjson::StringBuffer> rapidJsonWriter(rapidJsonBuffer);
    testRapidJson.Accept(rapidJsonWriter);
    ccTestEncoded = rapidJsonBuffer.GetString();
  }
  //
  unsigned int i(25000);
  do {
    generated = GlideJsonVs::generateJsonWithWs();
    // GlideJson:
    testGlideJson = GlideJson::Null;
    testEncoded.clear();
    start = std::chrono::steady_clock::now();
    testGlideJson = GlideJson::parse(generated.first);
    timerPGlideJson += std::chrono::steady_clock::now() - start;
    start = std::chrono::steady_clock::now();
    testEncoded = testGlideJson.toJson();
    timerEGlideJson += std::chrono::steady_clock::now() - start;
    //
    if(testEncoded != generated.first) {
      GlideJsonVs::errors.push_back("The generated JSON:\n\n" + generated.first + "\n\n... does not match:\n\n" + testEncoded + "\n");
    }
    else {
      // JSON for Modern C++:
      testJfmc = nlohmann::json::parse("null");
      testEncoded.clear();
      start = std::chrono::steady_clock::now();
      testJfmc = nlohmann::json::parse(generated.first);
      timerPJfmc += std::chrono::steady_clock::now() - start;
      start = std::chrono::steady_clock::now();
      testEncoded = testJfmc.dump();
      timerEJfmc += std::chrono::steady_clock::now() - start;
      // std::cout << "\n" << testEncoded << "\n";
      // JsonCpp:
      testInJsonCpp.str("null");
      testInJsonCpp >> testJsonCpp;
      testInJsonCpp.str(generated.first);
      testOutJsonCpp.str("");
      start = std::chrono::steady_clock::now();
      testInJsonCpp >> testJsonCpp;
      timerPJsonCpp += std::chrono::steady_clock::now() - start;
      start = std::chrono::steady_clock::now();
      testOutJsonCpp << testJsonCpp;
      timerEJsonCpp += std::chrono::steady_clock::now() - start;
      // std::cout << "\n" << testOutJsonCpp.str() << "\n";
      // cJSON:
      cGenerated = generated.first.data();
      cGeneratedSize = generated.first.size();
      start = std::chrono::steady_clock::now();
      cJsonTest = cJSON_ParseWithLength(cGenerated, cGeneratedSize);
      timerPCJson += std::chrono::steady_clock::now() - start;
      start = std::chrono::steady_clock::now();
      cTestEncoded = cJSON_PrintUnformatted(cJsonTest);
      timerECJson += std::chrono::steady_clock::now() - start;
      cJSON_Delete(cJsonTest);
      free(cTestEncoded);
      if(cJsonTest == NULL) {
        GlideJsonVs::errors.push_back("The generated JSON:\n\n" + generated.first + "\n\n... caused cJSON to fail!\n");
      }
      // std::cout << "\n" << cTestEncoded << "\n";
      // RapidJSON:
      testRapidJson.Parse("null");
      cGenerated = generated.first.data();
      cGeneratedSize = generated.first.size();
      start = std::chrono::steady_clock::now();
      testRapidJson.Parse(cGenerated);
      timerPRapidJson += std::chrono::steady_clock::now() - start;
      start = std::chrono::steady_clock::now();
      {
        rapidjson::StringBuffer rapidJsonBuffer;
        rapidjson::Writer<rapidjson::StringBuffer> rapidJsonWriter(rapidJsonBuffer);
        testRapidJson.Accept(rapidJsonWriter);
        ccTestEncoded = rapidJsonBuffer.GetString();
        // std::cout << "\n" << ccTestEncoded << "\n";
      }
      timerERapidJson += std::chrono::steady_clock::now() - start;
      // GlideJson (with whitespace):
      testGlideJson = GlideJson::Null;
      testEncoded.clear();
      start = std::chrono::steady_clock::now();
      testGlideJson = GlideJson::parse(generated.second);
      timerPGlideJson += std::chrono::steady_clock::now() - start;
      start = std::chrono::steady_clock::now();
      testEncoded = testGlideJson.toJson();
      timerEGlideJson += std::chrono::steady_clock::now() - start;
      //
      if(testEncoded != generated.first) {
        GlideJsonVs::errors.push_back("The generated JSON:\n\n" + generated.second + "\n\n... does not match:\n\n" + testEncoded + "\n");
      }
      else {
        // JSON for Modern C++ (with whitespace):
        testJfmc = nlohmann::json::parse("null");
        testEncoded.clear();
        start = std::chrono::steady_clock::now();
        testJfmc = nlohmann::json::parse(generated.second);
        timerPJfmc += std::chrono::steady_clock::now() - start;
        start = std::chrono::steady_clock::now();
        testEncoded = testJfmc.dump();
        timerEJfmc += std::chrono::steady_clock::now() - start;
        // std::cout << "\n" << testEncoded << "\n";
        // JsonCpp (with whitespace):
        testInJsonCpp.str("null");
        testInJsonCpp >> testJsonCpp;
        testInJsonCpp.str(generated.second);
        testOutJsonCpp.str("");
        start = std::chrono::steady_clock::now();
        testInJsonCpp >> testJsonCpp;
        timerPJsonCpp += std::chrono::steady_clock::now() - start;
        start = std::chrono::steady_clock::now();
        testOutJsonCpp << testJsonCpp;
        timerEJsonCpp += std::chrono::steady_clock::now() - start;
        // std::cout << "\n" << testOutJsonCpp.str() << "\n";
        // cJSON:
        cGenerated = generated.second.data();
        cGeneratedSize = generated.second.size();
        start = std::chrono::steady_clock::now();
        cJsonTest = cJSON_ParseWithLength(cGenerated, cGeneratedSize);
        timerPCJson += std::chrono::steady_clock::now() - start;
        start = std::chrono::steady_clock::now();
        cTestEncoded = cJSON_PrintUnformatted(cJsonTest);
        timerECJson += std::chrono::steady_clock::now() - start;
        cJSON_Delete(cJsonTest);
        free(cTestEncoded);
        if(cJsonTest == NULL) {
          GlideJsonVs::errors.push_back("The generated JSON:\n\n" + generated.second + "\n\n... caused cJSON to fail!\n");
        }
        // std::cout << "\n" << cTestEncoded << "\n";
        // RapidJSON:
        testRapidJson.Parse("null");
        cGenerated = generated.second.data();
        cGeneratedSize = generated.second.size();
        start = std::chrono::steady_clock::now();
        testRapidJson.Parse(cGenerated);
        timerPRapidJson += std::chrono::steady_clock::now() - start;
        start = std::chrono::steady_clock::now();
        {
          rapidjson::StringBuffer rapidJsonBuffer;
          rapidjson::Writer<rapidjson::StringBuffer> rapidJsonWriter(rapidJsonBuffer);
          testRapidJson.Accept(rapidJsonWriter);
          ccTestEncoded = rapidJsonBuffer.GetString();
          // std::cout << "\n" << ccTestEncoded << "\n";
        }
        timerERapidJson += std::chrono::steady_clock::now() - start;
        //
      }
    }
  }
  while(--i > 0);
  std::cout
    <<     "\nGlideJson parsing:            "
    << std::chrono::duration_cast<std::chrono::microseconds>(timerPGlideJson).count()
    << "us\nGlideJson encoding:           "
    << std::chrono::duration_cast<std::chrono::microseconds>(timerEGlideJson).count()
    << "us\n\nJSON for Modern C++ parsing:  "
    << std::chrono::duration_cast<std::chrono::microseconds>(timerPJfmc).count()
    << "us\nJSON for Modern C++ encoding: "
    << std::chrono::duration_cast<std::chrono::microseconds>(timerEJfmc).count()
    << "us\n\nJsonCpp parsing:              "
    << std::chrono::duration_cast<std::chrono::microseconds>(timerPJsonCpp).count()
    << "us\nJsonCpp encoding:             "
    << std::chrono::duration_cast<std::chrono::microseconds>(timerEJsonCpp).count()
    << "us\n\ncJSON parsing:                "
    << std::chrono::duration_cast<std::chrono::microseconds>(timerPCJson).count()
    << "us\ncJSON encoding:               "
    << std::chrono::duration_cast<std::chrono::microseconds>(timerECJson).count()
    << "us\n\nRapidJSON parsing:            "
    << std::chrono::duration_cast<std::chrono::microseconds>(timerPRapidJson).count()
    << "us\nRapidJSON encoding:           "
    << std::chrono::duration_cast<std::chrono::microseconds>(timerERapidJson).count()
    << "us\n\n";
}

int GlideJsonVs::run() {
  std::srand(std::time(NULL));
  GlideJsonVs::testJson();
  // Check errors:
  size_t errorCount(GlideJsonVs::errors.size());
  if(errorCount) {
    std::cout << "\n--- " << errorCount << " ERRORS ---\n\n";
    size_t i(0);
    do {
      std::cout << GlideJsonVs::errors[i] << "\n";
    }
    while(++i < errorCount);
    return 1;
  }
  return 0;
}

int main(int argc, char *argv[]) {
  (void)argc;
  (void)argv;
  return GlideJsonVs::run();
}
