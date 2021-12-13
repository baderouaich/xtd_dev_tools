cmake_minimum_required(VERSION 3.3)

# Project
project(xtd_dev_tools)
find_package(xtd REQUIRED)
add_sources(  
  src/pch.hpp

  src/main_form.hpp
  src/main_form.cpp

  src/enum_stringifier_form/enum_stringifier_form.hpp
  src/enum_stringifier_form/enum_stringifier_form.cpp
  src/enum_stringifier_form/enum_parser.hpp
)
target_type(GUI_APPLICATION)

# PCH
target_precompile_headers(${PROJECT_NAME} PRIVATE src/pch.hpp)

# Install
install_component()
