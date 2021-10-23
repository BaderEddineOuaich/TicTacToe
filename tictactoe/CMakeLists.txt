cmake_minimum_required(VERSION 3.3)

# Project
project(tictactoe)
find_package(xtd REQUIRED)
add_sources(
  pch.h
  src/form1.h
  src/form1.cpp
)
target_type(GUI_APPLICATION)

# PCH
target_precompile_headers(tictactoe PRIVATE pch.h)

# Install
install_component()