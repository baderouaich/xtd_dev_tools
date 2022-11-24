#include "../pch.hpp"
#include "enum_stringifier_form.hpp"
#include "enum_parser.hpp"
using namespace xtd;
using namespace xtd::forms;
using namespace xtd_dev_tools;

enum_stringifier_form::enum_stringifier_form()
{
  text("Enum Stringifier");
  client_size({640, 480}).minimum_size(client_size()).maximum_size(client_size());
  auto_size_mode(auto_size_mode::grow_and_shrink);


  m_enum_string_input_txtbx.parent(*this);
  m_enum_string_input_txtbx.location({0,0});
  m_enum_string_input_txtbx.text("Enum string here...");
  m_enum_string_input_txtbx.size({ client_size().width(), client_size().height() / 2 });
  m_enum_string_input_txtbx.font(drawing::font(drawing::system_fonts::default_font(), 12.0f));
  m_enum_string_input_txtbx.multiline(true);
  m_enum_string_input_txtbx.word_wrap(false);

  m_stringify_enum_btn.parent(*this);
  m_stringify_enum_btn.text("Stringify");
  m_stringify_enum_btn.size({ 150, 45 });
  m_stringify_enum_btn.location({(width() - 150 ) / 2,  m_enum_string_input_txtbx.location().y() + m_enum_string_input_txtbx.size().height() + 5});
  m_stringify_enum_btn.font(drawing::font(drawing::system_fonts::default_font(), 10.0f));
  m_stringify_enum_btn.click += [this]
  {
    m_enum_string_output_txtbx.text(stringify_enum_str(m_enum_string_input_txtbx.text()));
  };
    
  m_enum_string_output_txtbx.parent(*this);
  m_enum_string_output_txtbx.location({ 0,  m_stringify_enum_btn.location().y() + m_stringify_enum_btn.size().height() + 5 });
  m_enum_string_output_txtbx.size({ client_size().width(), height() / 3});
  m_enum_string_output_txtbx.font(drawing::font(drawing::system_fonts::default_font(), 10.0f));
  m_enum_string_output_txtbx.multiline(true);
  m_enum_string_output_txtbx.word_wrap(true);
  m_enum_string_output_txtbx.read_only(true);
}


xtd::ustring enum_stringifier_form::stringify_enum_str(const xtd::ustring& enum_str) try
{
  std::unique_ptr<enum_parser> enum_parser_ptr(new enum_parser(enum_str));

  std::ostringstream ostream_oss{};

  ostream_oss << "template<> struct xtd::enum_register<" << enum_parser_ptr->name_with_namespace() << "> {" << std::endl
  << "  explicit operator auto() const {return xtd::enum_collection<" << enum_parser_ptr->name_with_namespace() << "> {";
  for (std::size_t i = 0; i < enum_parser_ptr->values.size(); ++i)
  {
    const auto& [enum_member, value] = enum_parser_ptr->values[i];
    //{progress_box_options::none, "none"},
    ostream_oss << '{' << enum_parser_ptr->name_with_namespace() << "::" << enum_member << ", \"" << enum_member << "\"}";
    if (i != enum_parser_ptr->values.size() - 1)
    {
      ostream_oss << ", ";
    }
    else
    {
      ostream_oss << "};}" << std::endl << "};";
    }
    //{progress_box_options::none, L"none"},
  }

  return ostream_oss.str();
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
