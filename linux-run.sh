#!/usr/bin/env bash

set -e

rm -rf NativeExtensionInSwift/.build

echo "run command: swift build"
swift build --package-path NativeExtensionInSwift

echo "run command: npm install"
npm install --unsafe-perm

echo "run command: node index.js"
node index.js
