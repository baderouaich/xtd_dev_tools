/// @file
/// @brief Contains enum_stringifier_form class.
#pragma once
#include <xtd/xtd.forms>

/// @brief Represents the namespace that contains application objects.
namespace xtd_dev_tools {
  /// @brief Represents the main form.
  class enum_stringifier_form : public xtd::forms::form {
  public:
    /// @brief Initializes a new instance of the enum_stringifier_form class.
    enum_stringifier_form();

    xtd::ustring stringify_enum_str(const xtd::ustring& enum_str);

  private:
    //xtd::forms::vertical_layout_panel m_vertical_layout;
    //xtd::forms::vertical_layout_panel m_panel;
    xtd::forms::text_box m_enum_string_input_txtbx{};
    xtd::forms::text_box m_enum_string_output_txtbx{};
    xtd::forms::button m_copy_btn;
    xtd::forms::button m_stringify_enum_btn{};
  };



}
