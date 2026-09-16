cmake_minimum_required (VERSION 3.10)

set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")

if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("Autoclicker")

add_executable (Autoclicker "Autoclicker.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Autoclicker PROPERTY CXX_STANDARD 20)
endif()

