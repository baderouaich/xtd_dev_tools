/// @file
/// @brief Contains main_form class.
#pragma once
#include <xtd/xtd.forms>
#include "enum_stringifier_form/enum_stringifier_form.hpp"

/// @brief Represents the namespace that contains application objects.
namespace xtd_dev_tools {
  /// @brief Represents the main form.
  class main_form : public xtd::forms::form {
  public:
    /// @brief Initializes a new instance of the main_form class.
    main_form();

    /// @brief The main entry point for the application.
    static void main();

    void open_enum_stringifier(){
      //visible(false);

      std::unique_ptr<enum_stringifier_form> esf_ptr(new enum_stringifier_form());
      esf_ptr->show_dialog();

      //visible(true);
    }

  private: // todo fix menu item
    xtd::forms::menu_item m_enum_stringifier_menu_item{ "Enum Stringifier", {*this, overload_<>(&main_form::open_enum_stringifier)}, xtd::forms::menu_images::edit_cut(), xtd::forms::shortcut::cmd_e };
    xtd::forms::menu_item m_tools_menu_item_options{ "Tools", { m_enum_stringifier_menu_item } };
    xtd::forms::main_menu m_main_menu{ m_tools_menu_item_options, };

  };



}
