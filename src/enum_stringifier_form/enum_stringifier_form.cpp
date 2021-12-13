#include "../pch.hpp"
#include "enum_stringifier_form.hpp"
#include "enum_parser.hpp"
using namespace xtd;
using namespace xtd::forms;
using namespace xtd_dev_tools;



enum_stringifier_form::enum_stringifier_form()
{

}


xtd::ustring enum_stringifier_form::stringify_enum_str(const xtd::ustring& enum_str) try
{
  std::unique_ptr<enum_parser> enum_parser_ptr(new enum_parser(enum_str));

  std::ostringstream ostream_oss{};
  std::ostringstream wostream_oss{};

  ostream_oss << "inline std::ostream& operator<<(std::ostream& os, const " << enum_parser_ptr->name << " value) { return os << to_string(value, { ";
  wostream_oss << "inline std::wostream& operator<<(std::wostream& os, const " << enum_parser_ptr->name << " value) { return os << to_string(value, { ";
  for (std::size_t i = 0; i < enum_parser_ptr->values.size(); ++i)
  {
    const auto& [enum_member, value] = enum_parser_ptr->values[i];
    //{progress_box_options::none, "none"},
    ostream_oss << '{' << enum_parser_ptr->name << "::" << enum_member << ", \"" << enum_member << "\"}";
    wostream_oss << '{' << enum_parser_ptr->name << "::" << enum_member << ", L\"" << enum_member << "\"}";
    if (i != enum_parser_ptr->values.size() - 1)
    {
      ostream_oss << ", ";
      wostream_oss << ", ";
    }
    else
    {
      ostream_oss << "}); }";
      wostream_oss << "}); }";
    }
    //{progress_box_options::none, L"none"},
  }

  return ostream_oss.str() + '\n' + wostream_oss.str();
}
catch (const std::exception& e)
{
  ustring msg(e.what());
  debug_message_box::show(*this, msg);
  return msg;
}
catch (...)
{
  ustring msg("UNKNOWN ERROR");
  debug_message_box::show(*this, msg);
  return msg;
}
