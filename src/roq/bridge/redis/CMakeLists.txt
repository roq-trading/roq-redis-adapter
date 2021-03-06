set(TARGET_NAME "${PROJECT_NAME}")

add_subdirectory(flags)

set(SOURCES application.cpp config.cpp controller.cpp main.cpp)

add_executable("${TARGET_NAME}" ${SOURCES})

target_link_libraries(
  "${TARGET_NAME}"
  PRIVATE "${TARGET_NAME}-flags"
          "${PROJECT_NAME}-hiredis"
          roq-client::roq-client
          roq-io::roq-io
          roq-logging::roq-logging
          roq-api::roq-api
          fmt::fmt
          absl::flags
          ${HIREDIS_LIBRARIES}
          ${LIBEVENT_LIBRARIES}
          ${UUID_LIBRARIES}
          ${RT_LIBRARIES})

target_compile_features("${TARGET_NAME}" PUBLIC cxx_std_20)

set_target_properties("${TARGET_NAME}" PROPERTIES LINK_FLAGS_RELEASE -s)

target_compile_definitions(
  "${TARGET_NAME}"
  PRIVATE ROQ_PACKAGE_NAME="${TARGET_NAME}" ROQ_BUILD_VERSION="${GIT_REPO_VERSION}"
          ROQ_GIT_DESCRIBE_HASH="${GIT_DESCRIBE_HASH}" ROQ_BUILD_NUMBER="${GIT_DESCRIBE_NUMBER}"
          ROQ_BUILD_TYPE="${ROQ_BUILD_TYPE}")

install(TARGETS ${TARGET_NAME})
