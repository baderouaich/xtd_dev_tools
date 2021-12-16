#pragma once
#include <xtd/xtd.h>
using namespace xtd;

struct enum_parser
{
  enum_parser(const ustring& enum_str) noexcept(false)
  {
    // Processing enum string line by line
    std::istringstream ss(enum_str);
    ustring line{};
    while (getline(ss, line, '\n'))
    {
      // Trim left right spaces
      line = line.trim();

      // Validate line, skip what we don't need
      if (line.empty()) continue;
      if (line.starts_with("//")) continue; // skip comments
      if (line.starts_with("/*")) continue; // skip comments
      if (line.starts_with("*/")) continue; // skip comments
      if (line.starts_with("{")) continue; //  skip brackets opening {
      if (line.starts_with("}")) continue; //  skip brackets closing }

      // If we're at the beginning of an enum class
      if (line.starts_with("enum class"))
      {
        // extract name which is expected to be the next thing after "enum class"
        auto name_begin_idx = line.last_index_of("enum class") + std::strlen("enum class");
        auto name_end_idx = line.last_index_of('{') - name_begin_idx;
        if (name_end_idx == ustring::npos) name_end_idx = line.size() - 1; // '{' can be at the next line
        name = line.substr(name_begin_idx, name_end_idx).trim(); // extract enum class's name
      }
      // If we're at the beginning of an enum (check enum class before enum, order matter)
      else if (line.starts_with("enum"))
      {
        // extract name which is expected to be the next thing after "enum"
        auto name_begin_idx = line.last_index_of("enum") + std::strlen("enum");
        auto name_end_idx = line.last_index_of('{') - name_begin_idx;
        if (name_end_idx == ustring::npos) name_end_idx = line.size() - 1; // '{' can be at the next line
        name = line.substr(name_begin_idx, name_end_idx).trim(); // extract enum's name
      }
      else // must be enum value
      {
        // Lets check if type is [enum_member=value] or [enum_member] 
        if (line.find('=') != ustring::npos) // if it's a [enum_member=value]
        {
          // Pop ',' at the end if available
          if (line.back() == ',') line.remove(line.size() - 1);

          // Split line at '='
          auto parts = line.split({ '=' });
          std::pair<ustring, std::optional<ustring>> value{};
          value.first = parts[0].trim(); // and trim in case there is a space before or after '='
          value.second = parts[1].trim();
          values.push_back(value);
        }
        else // if it's a [enum_member] only
        {
          // Pop ',' at the end if available
          if (line.back() == ',') line.remove(line.size() - 1);

          // now the line itself becomes the [enum_member]
          std::pair<ustring, std::optional<ustring>> value{ line.trim(), std::nullopt };
          values.push_back(value);
        }
      }
    }
  }

  ustring name; // enum name
  std::vector<std::pair<ustring, std::optional<ustring>>> values; // enum values
};

//using namespace xtd::tunit;
//class test_class_(test_enum_parser) {
//public:
//  void test_method_(perform_test) {
//    enum_parser p("//");
//    tunit::assert::are_equal(p.name, "", csf_);
//  }
//
//};