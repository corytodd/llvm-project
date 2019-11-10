//===--- PTITidyModule.cpp - clang-tidy -----------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "../ClangTidy.h"
#include "../ClangTidyModule.h"
#include "../ClangTidyModuleRegistry.h"
#include "FunctionNameFormatCheck.h"

namespace clang {
namespace tidy {
namespace pti {

class PTIModule : public ClangTidyModule {
public:
  void addCheckFactories(ClangTidyCheckFactories &CheckFactories) override {
    CheckFactories.registerCheck<FunctionNameFormatCheck>(
        "pti-function-name-format");
  }
};

} // namespace pti

// Register the PTITidyModule using this statically initialized variable.
static ClangTidyModuleRegistry::Add<pti::PTIModule>
    X("pti-module", "Adds PTI clang-tidy checks.");

// This anchor is used to force the linker to link in the generated object file
// and thus register the PTIModule.
volatile int PTIModuleAnchorSource = 0;

} // namespace tidy
} // namespace clang
