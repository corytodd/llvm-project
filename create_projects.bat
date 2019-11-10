mkdir build_release
pushd build_release
cmake -G Ninja -DLLVM_ENABLE_PROJECTS="clang;libcxx;libcxxabi;clang-tools-extra" -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=H:\build_llvm ../llvm 
popd