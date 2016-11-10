#!/bin/bash

# Target architectures
ARCHS="i386 x86_64 armv7 armv7s arm64"

for ARCH in $ARCHS; do
    python waf configure --cxx_mkspec=cxx_ios70_apple_llvm_$ARCH
    python waf fix_bundle_dependencies
    python waf build
    rm -rf /tmp/$ARCH/
    python waf install --install_path=/tmp/$ARCH/ --install_static_libs
done

# Static libraries
LIBS="libcpuid.a libfifi.a libfifi_calc.a"

echo "#### Fat static libs including $ARCHS:"

for LIB in $LIBS; do
    LIPO_ARGS=""
    for ARCH in $ARCHS; do
        LIPO_ARGS+="/tmp/$ARCH/$LIB "
    done
    lipo -create $LIPO_ARGS -output FifiCalc/$LIB
    du -h FifiCalc/$LIB
    lipo -info FifiCalc/$LIB
done
	
echo "#### Finished."
