@_cdecl("swift_fibonacci")
public func fibonacci(_ n: CInt) -> CInt {
    if n == 0 {
        return 0
    } else if n == 1{
        return 1
    }
    return fibonacci(n - 1) + fibonacci(n - 2)
}

@_cdecl("swift_print_hello")
public func printHello() {
    print("hello")
}