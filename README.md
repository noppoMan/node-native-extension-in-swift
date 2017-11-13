# node-native-extension-in-swift

<img width="180" src="https://www.shareicon.net/data/512x512/2015/10/06/112654_apple_512x512.png">　　　<img width="230" src="https://nodejs.org/static/images/logos/nodejs-new-pantone-black.png">

An experimental repo for [Node.js native addons](https://nodejs.org/api/addons.html) that written in Swift.  
The first motivation of implementeing this was reduceing overhead of execution between Node.js and Swift on the Serverless environment.

# Usage

## Linux

```sh
$ docker build -t node-native-extension-in-swift .
$ docker run -t node-native-extension-in-swift
```

## Mac

```sh
$ git clone https://github.com/noppoMan/node-native-extension-in-swift.git
$ cd node-native-extension-in-swift
$ swift build --package-path NativeExtensionInSwift
$ npm i
$ node index.js
```

## License
node-native-extension-in-swift is released under the MIT license. See LICENSE for details.
