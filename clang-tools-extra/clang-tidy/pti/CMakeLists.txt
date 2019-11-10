set(LLVM_LINK_COMPONENTS support)

add_clang_library(clangTidyPTIModule
  FunctionNameFormatCheck.cpp
  PTITidyModule.cpp
  
  LINK_LIBS
  clangAnalysis
  clangAST
  clangASTMatchers
  clangBasic
  clangLex
  clangTidy
  clangTidyUtils
  clangTooling
  clangStaticAnalyzerCheckers
  )
