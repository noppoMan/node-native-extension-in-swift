# node-native-extension-in-swift

<img width="180" src="https://www.shareicon.net/data/512x512/2015/10/06/112654_apple_512x512.png">　　　<img width="230" src="https://nodejs.org/static/images/logos/nodejs-new-pantone-black.png">

An experimental repo for [Node.js native addons](https://nodejs.org/api/addons.html) that written in Swift.  
The first motivation of implementeing this was reduceing overhead of execution between Node.js and Swift on the Serverless environment.

## Writing native extensions with Swift

1. Define function(s) in a format that can be exported to C/C++ in Swift side.

```swift
@_cdecl("swift_fibonacci") // Name the function symbol.
public func fibonacci(_ n: CInt) -> CInt {
    if n == 0 {
        return 0
    } else if n == 1{
        return 1
    }
    return fibonacci(n - 1) + fibonacci(n - 2)
}
```

2. [Register fibonacci as callable function in Node.js (V8 side)](https://github.com/noppoMan/node-native-extension-in-swift/blob/master/swift.cc#L53)

3. The exported functions can be imported and executed in Node.js side.

```js
const swift = require('bindings')('swift');

const result = swift.fibonacci(10);
console.log(result);
```


## Running Example

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
