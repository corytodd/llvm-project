//===--- FunctionNameFormatCheck.cpp - clang-tidy -------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "FunctionNameFormatCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include <regex>
#include <algorithm>
#include <cctype>

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace pti {

void FunctionNameFormatCheck::registerMatchers(MatchFinder *Finder) {
  // Only enforce on C language
  if(!(getLangOpts().C11 || getLangOpts().C99)) 
    return;
  Finder->addMatcher(functionDecl().bind("fnName"), this);
}

void FunctionNameFormatCheck::check(const MatchFinder::MatchResult &Result) {

  static std::regex reg("[A-Z0-9]+_[A-Z](\\w|\\d)*");
  const auto *MatchedDecl = Result.Nodes.getNodeAs<FunctionDecl>("fnName");
  const auto fnName = MatchedDecl->getName().str();

  if (std::regex_match(fnName, reg))
    return;

  diag(MatchedDecl->getLocation(), "invalid case style for function %0")
      << MatchedDecl;
  diag(MatchedDecl->getLocation(), "fix function name", DiagnosticIDs::Note)
      << FixItHint::CreateInsertion(MatchedDecl->getLocation(), fixupFunctionName(fnName));
}

std::string FunctionNameFormatCheck::fixupFunctionName(const std::string& name) {
  
  std::string fixed;
  std::string moduleName;
  std::string funcName;
  
  // If there is no underscore, assume the module name is missing entirely
  auto underscore = name.find('_');
  if(underscore == std::string::npos) {    
    moduleName = "MODULE";    
    funcName = std::string(name);
  } else {
    moduleName = name.substr(0, underscore);
    // Skip _
    funcName = name.substr(underscore+1);
  }

  // Module name to ALL CAPS 
  std::transform(moduleName.begin(), moduleName.end(), moduleName.begin(), 
      [](unsigned char c){ return std::toupper(c); }
  );
  fixed.append(moduleName);

  fixed.push_back('_');

  // Force function name to Uppercase
  std::transform(funcName.begin(), funcName.begin() + 1, funcName.begin(), 
      [](unsigned char c){ return std::toupper(c); }
  );

  // Too much work to interpret PascalCase so call this good enough
  fixed.append(funcName);

  return fixed;

}

} // namespace pti
} // namespace tidy
} // namespace clang
