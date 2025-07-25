// swift-tools-version: 5.9
// The swift-tools-version declares the minimum version of Swift required to build this package.

import PackageDescription

let package = Package(
    name: "swift",
    platforms: [
        .macOS(.v10_15),
    ],
    products: [
        .library(
            name: "cote",
            targets: ["cote"]
        ),
        .library(
            name: "algorithm",
            targets: ["algorithm"]
        ),
    ],
    dependencies: [
        .package(url: "https://github.com/Quick/Quick.git", from: "6.0.0"),
        .package(url: "https://github.com/Quick/Nimble.git", from: "12.0.0"),
        .package(url: "https://github.com/apple/swift-collections.git", .upToNextMinor(from: "1.2.0")),
    ],
    targets: [
        .target(
            name: "algorithm",
            dependencies: [.product(name: "Collections", package: "swift-collections")]
        ),
        .target(
            name: "cote",
            dependencies: [.product(name: "Collections", package: "swift-collections")]
        ),
        .testTarget(
            name: "coteTests",
            dependencies: [
                "cote",
                .product(name: "Quick", package: "Quick"),
                .product(name: "Nimble", package: "Nimble"),
            ],
            path: "Tests/cote"
        ),
        .testTarget(
            name: "algorithmTests",
            dependencies: [
                "algorithm",
                .product(name: "Quick", package: "Quick"),
                .product(name: "Nimble", package: "Nimble"),
            ],
            path: "Tests/algorithm"
        ),
    ]
)
