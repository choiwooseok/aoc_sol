#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

std::vector<std::vector<std::string>> readLines(const std::string& fileName) {
  std::fstream inputs(fileName);
  std::vector<std::vector<std::string>> data;

  std::vector<std::string> lines;
  std::string line;
  while (std::getline(inputs, line)) {
    if (line != "") {
      lines.push_back(line);
    } else {
      data.push_back(lines);
      lines.clear();
    }
  }
  inputs.close();
  return data;
}

std::vector<std::string> split(const std::string& source, const std::string& delim) {
  size_t pos_start = 0, pos_end, delim_len = delim.length();
  std::vector<std::string> res;

  while ((pos_end = source.find(delim, pos_start)) != std::string::npos) {
    std::string token = source.substr(pos_start, pos_end - pos_start);
    pos_start = pos_end + delim_len;
    res.push_back(token);
  }

  res.push_back(source.substr(pos_start));
  return res;
}

void ignoreCid(std::vector<std::string>& fields, int& cnt) {
  if (fields.size() == 7) {
    bool hasCid = false;
    for (auto& field : fields) {
      if (field.find("cid") != std::string::npos) {
        hasCid = true;
        break;
      }
    }
    if (!hasCid) {
      cnt++;
    }
  }
}

void part1(const std::vector<std::vector<std::string>>& data) {
  int cnt = 0;
  for (auto& passport : data) {
    std::vector<std::string> fields;
    for (auto& line : passport) {
      std::vector<std::string> parts = split(line, " ");
      for (auto& part : parts) {
        fields.push_back(part);
      }
    }
    if (fields.size() == 8) {
      cnt++;
    }
    ignoreCid(fields, cnt);
  }
  std::cout << cnt << std::endl;
}

bool isValidByr(const std::string& value) {
  int year = std::stoi(value);
  return year >= 1920 && year <= 2002;
}

bool isValidIyr(const std::string& value) {
  try {
    int year = std::stoi(value);
    return year >= 2010 && year <= 2020;
  } catch (std::exception& e) {
    return false;
  }
}

bool isValidEyr(const std::string& value) {
  try {
    int year = std::stoi(value);
    return year >= 2020 && year <= 2030;
  } catch (std::exception& e) {
    return false;
  }
}

bool isValidHgt(const std::string& value) {
  try {
    std::string unit = value.substr(value.size() - 2);
    int height = std::stoi(value.substr(0, value.size() - 2));
    if (unit == "cm") {
      return height >= 150 && height <= 193;
    } else if (unit == "in") {
      return height >= 59 && height <= 76;
    }
    return false;
  } catch (std::exception& e) {
    return false;
  }
}

bool isValidHcl(const std::string& value) {
  bool valid = false;
  if (value[0] == '#' && value.size() == 7) {
    bool validHcl = true;
    for (int i = 1; i < value.size(); i++) {
      if (!isxdigit(value[i])) {
        validHcl = false;
        break;
      }
    }
    if (validHcl) {
      valid = true;
    }
  }
  return valid;
}

bool isValidPid(const std::string& value) {
  if (value.size() == 9) {
    bool validPid = true;
    for (int i = 0; i < value.size(); i++) {
      if (!isdigit(value[i])) {
        validPid = false;
        break;
      }
    }
    if (validPid) {
      return true;
    }
  }
  return false;
}

bool isValidEcl(const std::string& value) {
  std::vector<std::string> validEcl = {"amb", "blu", "brn", "gry", "grn", "hzl", "oth"};
  return std::find(validEcl.begin(), validEcl.end(), value) != validEcl.end();
}

void part2(std::vector<std::vector<std::string>>& data) {
  int cnt = 0;
  for (auto& passport : data) {
    std::vector<std::string> fields;
    for (auto& line : passport) {
      std::vector<std::string> parts = split(line, " ");
      for (auto& part : parts) {
        fields.push_back(part);
      }
    }

    bool valid = true;
    for (auto& field : fields) {
      std::vector<std::string> kv = split(field, ":");
      std::string key = kv[0];
      std::string value = kv[1];

      if (key == "byr") {
        valid &= isValidByr(value);
      }

      if (key == "iyr") {
        valid &= isValidIyr(value);
      }

      if (key == "eyr") {
        valid &= isValidEyr(value);
      }

      if (key == "hgt") {
        valid &= isValidHgt(value);
      }

      if (key == "hcl") {
        valid &= isValidHcl(value);
      }

      if (key == "ecl") {
        valid &= isValidEcl(value);
      }

      if (key == "pid") {
        valid &= isValidPid(value);
      }
    }

    if (valid) {
      if (fields.size() == 8) {
        cnt++;
      } else {
        ignoreCid(fields, cnt);
      }
    }
  }

  std::cout << cnt << std::endl;
}

int main(int argc, char** argv) {
  std::vector<std::vector<std::string>> data = readLines("input.txt");

  part1(data);
  part2(data);

  return 0;
}