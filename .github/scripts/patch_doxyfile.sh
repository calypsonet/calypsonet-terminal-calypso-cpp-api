#!/bin/sh

echo "Compute the current API version..."
version=$1

if [ "$version" = "" ]; then
  # SNAPSHOT version
  version="$(sed -rn 's/.*MAJOR.*\"(.*)\".*/\1/p' CMakeLists.txt).$(sed -rn 's/.*MINOR.*\"(.*)\".*/\1/p' CMakeLists.txt).$(sed -rn 's/.*PATCH.*\"(.*)\".*/\1/p' CMakeLists.txt)-SNAPSHOT"
fi

echo "Computed current API version: $version"

sed -i "s/%PROJECT_VERSION%/$version/g" ./.github/doxygen/Doxyfile