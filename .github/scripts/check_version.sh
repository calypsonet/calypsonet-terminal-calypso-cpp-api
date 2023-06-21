#!/bin/sh

tag=$1
echo "Input tag: '$tag'"

major="$(sed -rn 's/.*MAJOR.*\"(.*)\".*/\1/p' CMakeLists.txt)"
minor="$(sed -rn 's/.*MINOR.*\"(.*)\".*/\1/p' CMakeLists.txt)"
patch="$(sed -rn 's/.*PATCH.*\"(.*)\".*/\1/p' CMakeLists.txt)"
tweak="$(sed -rn 's/.*TWEAK.*\"(.*)\".*/\1/p' CMakeLists.txt)"
version="$major.$minor.$patch"
if [ $tweak != "" ]; then
  version="$version.$tweak"
fi

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
  if [ "$(git tag -l "$version")" ]; then
    echo "ERROR: version '$version' has already been released, please increase the version number."
    exit 1
  fi
  version="$version-SNAPSHOT"
fi

echo "PROJECT_VERSION=$version" >> $GITHUB_ENV

echo "Retained PROJECT_VERSION=$version"