# node-native-extension-in-swift

An experimental repo for [Node.js native addons](https://nodejs.org/api/addons.html) that written in Swift.  
The first motivation of implementeing this was reduceing overhead of execution between Node.js and Swift on the Serverless environment.

## Usage

```
$ git clone https://github.com/noppoMan/node-native-extension-in-swift.git
$ cd node-native-extension-in-swift
$ swift build --package-path NativeExtensionInSwift
$ npm i
$ node index.js
```

## License
node-native-extension-in-swift is released under the MIT license. See LICENSE for details.
