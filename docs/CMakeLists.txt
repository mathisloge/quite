find_package(Python REQUIRED COMPONENTS Interpreter)

add_custom_target(doc_sphinx ALL
  COMMAND $<TARGET_FILE:Python::Interpreter> -m mkdocs build --config-file "${PROJECT_SOURCE_DIR}/mkdocs.yml"
  COMMENT "Building Sphinx documentation"
  VERBATIM
)
