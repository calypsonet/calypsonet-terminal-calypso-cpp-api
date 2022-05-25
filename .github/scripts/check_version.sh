#!/bin/sh

tag=$1
echo "Input tag: '$tag'"

version="$(sed -rn 's/.*MAJOR.*\"(.*)\".*/\1/p' CMakeLists.txt).$(sed -rn 's/.*MINOR.*\"(.*)\".*/\1/p' CMakeLists.txt).$(sed -rn 's/.*PATCH.*\"(.*)\".*/\1/p' CMakeLists.txt)"

echo "Version in 'CMakeLists.txt' file: '$version'"

if [ "$tag" != "" ]; then
  echo "Release mode: check version consistency..."
  if [ "$tag" != "$version" ]; then
    echo "ERROR: the tag '$tag' is different from the version '$version' in the 'CMakeLists.txt' file"
    exit 1
  fi
else
  echo "Snapshot mode: fetch existing tags..."
  git fetch --tags
  if [ $(git tag -l "$version") ]; then
    echo "ERROR: version '$version' has already been released"
    exit 1
  fi
fi
