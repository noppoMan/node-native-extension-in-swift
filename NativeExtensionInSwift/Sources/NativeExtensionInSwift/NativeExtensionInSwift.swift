public struct NativeExtensionInSwift {
    
    public func fibonacci(_ n: CInt) -> CInt {
        if n == 0 {
            return 0
        } else if n == 1{
            return 1
        }
        return fibonacci(n - 1) + fibonacci(n - 2)
    }
    
    public func printHello() {
        print("hello")
    }
}
