# Copyright [2017] [taurus.ai]
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

CMAKE_MINIMUM_REQUIRED(VERSION 3.7)
PROJECT(kungfu)

############################################################

SET(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules ${CMAKE_MODULE_PATH})

INCLUDE(GetGitRevisionDescription)
GET_GIT_HEAD_REVISION(GIT_REFSPEC GIT_HASH)

STRING(TIMESTAMP BUILDTIME "%Y%m%d%H%M%S")

SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Kungfu Master Trading System")
SET(CPACK_PACKAGE_NAME "${PROJECT_NAME}")
SET(CPACK_PACKAGE_VENDOR "taurus.ai")
SET(CPACK_PACKAGE_VERSION_MAJOR "0")
SET(CPACK_PACKAGE_VERSION_MINOR "0")
SET(CPACK_PACKAGE_VERSION_PATCH "1")

SET(CPACK_GENERATOR "RPM")
SET(CPACK_RPM_PACKAGE_RELEASE "${BUILDTIME}")
SET(CPACK_RPM_PACKAGE_ARCHITECTURE "x86_64")
SET(CPACK_RPM_PACKAGE_GROUP "${PROJECT_NAME}")
SET(CPACK_PACKAGE_DEFAULT_LOCATION "/opt/kungfu/master")
SET(CPACK_PACKAGING_INSTALL_PREFIX "/opt/kungfu/master")

############################################################
SET(TOOLCHAIN_DIR "/opt/kungfu/toolchain")

SET(BOOST_INCLUDEDIR "${TOOLCHAIN_DIR}/boost-1.62.0/include")
SET(BOOST_LIBRARYDIR "${TOOLCHAIN_DIR}/boost-1.62.0/lib")

SET(Boost_USE_MULTITHREADED ON)
SET(Boost_USE_STATIC_LIBS OFF)
SET(Boost_USE_STATIC_RUNTIME OFF)

FIND_PACKAGE(Boost 1.62.0 COMPONENTS locale date_time filesystem system thread serialization math_tr1 python chrono regex program_options REQUIRED)
INCLUDE_DIRECTORIES(${BOOST_INCLUDEDIR})

FIND_PACKAGE(PythonInterp)
FIND_PACKAGE(PythonLibs)
INCLUDE_DIRECTORIES(${PYTHON_INCLUDE_PATH})

SET(API_LIBRARYDIR "${CMAKE_CURRENT_SOURCE_DIR}/longfist/api/ctp/v6.3.6_20160606/lib")
LINK_DIRECTORIES(${API_LIBRARYDIR})

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
OPTION(BUILD_SHARED_LIBS "turn OFF for .a libs" ON)
OPTION(USE_SERVICE "use memory service" ON)
OPTION(USE_HASH_CODE "use hash code when writing" ON)
############################################################

ADD_SUBDIRECTORY(longfist)
ADD_SUBDIRECTORY(yijinjing)
ADD_SUBDIRECTORY(wingchun)

############################################################
SET(INFO_TXT_IN "${CMAKE_CURRENT_SOURCE_DIR}/rpm/INFO.txt")
SET(INFO_TXT    "${CMAKE_CURRENT_BINARY_DIR}/rpm/INFO.txt")
CONFIGURE_FILE(${INFO_TXT_IN} ${INFO_TXT})
SET(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_BINARY_DIR}/rpm/INFO.txt")

SET(CPACK_RPM_PRE_INSTALL_SCRIPT_FILE "${CMAKE_CURRENT_SOURCE_DIR}/rpm/scripts/pre_install.sh")
SET(CPACK_RPM_POST_INSTALL_SCRIPT_FILE "${CMAKE_CURRENT_SOURCE_DIR}/rpm/scripts/post_install.sh")
SET(CPACK_RPM_PRE_UNINSTALL_SCRIPT_FILE "${CMAKE_CURRENT_SOURCE_DIR}/rpm/scripts/pre_uninstall.sh")
SET(CPACK_RPM_POST_UNINSTALL_SCRIPT_FILE "${CMAKE_CURRENT_SOURCE_DIR}/rpm/scripts/post_uninstall.sh")

SET(CPACK_RPM_PACKAGE_REQUIRES "rfoo >= 1.3.1, pid >= 2.1.1, log4cplus2 == 2.0.0_RC1, supervisor >= 3.1.0")

INSTALL(DIRECTORY "${API_LIBRARYDIR}" DESTINATION "lib")
INSTALL(DIRECTORY "${BOOST_LIBRARYDIR}/" DESTINATION "lib/boost")

INSTALL(DIRECTORY "rpm/bin/" DESTINATION "bin")
INSTALL(DIRECTORY "rpm/etc/" DESTINATION "etc")

INSTALL(DIRECTORY "python/" DESTINATION "lib/python2.7/site-packages")

SET(CPACK_RPM_PACKAGE_AUTOREQ " no")
INCLUDE(CPack)