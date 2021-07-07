// swift-tools-version:5.3
import PackageDescription
let package = Package(
    name: "ROX",
    platforms: [
        .iOS(.v8), .tvOS(.v10)
    ],
    products: [
        .library(
            name: "ROX", 
            targets: ["ROX", "ROXCore"])
    ],
    targets: [
        .binaryTarget(
            name: "ROX", 
            path: "ROX.xcframework"),
        .binaryTarget(
            name: "ROXCore",
            path: "ROXCore.xcframework"
        )
    ])