cmake_minimum_required (VERSION 3.8)

# 如果支持，请为 MSVC 编译器启用热重载。
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

# keys are generated in the source tree by default
SET(CMAKE_DISABLE_SOURCE_CHANGES ON)
SET(CMAKE_DISABLE_IN_SOURCE_BUILD ON)

IF(NOT LCC_PROJECT_NAME)
		message(STATUS "You should define a variable LCC_PROJECT_NAME containing the name of the software you want to add a license to.\n \
		 A mock project named `DEFAULT` has been added for you.\n \
		 This project name should correspond to an existing project name in licensecc library. use `lcc project create` to create new projects.") 
	set(LCC_PROJECT_NAME "DEFAULT" CACHE STRING "Project name (name of the software for which you want to issue a license)") 
ENDIF(NOT LCC_PROJECT_NAME)


project ("license_demo" CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake/")



find_package(licensecc 2.0.0 REQUIRED)
message(STATUS "LicenseCC found " ${licensecc_DIR})


# 将源代码添加到此项目的可执行文件。
add_executable (license_demo src/license_demo.cpp)

cmake_policy(SET CMP0028 NEW)

target_link_libraries(license_demo licensecc::licensecc_static)

#run open-license-manager tests
INCLUDE(CTest)

# if (CMAKE_VERSION VERSION_GREATER 3.12)
#   set_property(TARGET license_demo PROPERTY CXX_STANDARD 20)
# endif()
