#
# Licensed to the Apache Software Foundation (ASF) under one
# or more contributor license agreements.  See the NOTICE file
# distributed with this work for additional information
# regarding copyright ownership.  The ASF licenses this file
# to you under the Apache License, Version 2.0 (the
# "License"); you may not use this file except in compliance
# with the License.  You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

cmake_minimum_required(VERSION 3.14)

project(XPlatform_lib)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenSSL REQUIRED)

if(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
	set(SYSCALL_SRC syscall_windows.cc)
else()
	set(SYSCALL_SRC syscall_linux.cc)
endif()

if(NOT OPENSSL_FOUND)
	message(FATAL_ERROR "Can't build without OpenSSL")
endif()

add_library(x_platform_utils_obj OBJECT ${SYSCALL_SRC} utils.cc dirent.cc)
target_include_directories(x_platform_utils_obj PRIVATE ${OPENSSL_INCLUDE_DIR})
target_link_libraries(x_platform_utils_obj PRIVATE ${OPENSSL_CRYPTO_LIBRARY})