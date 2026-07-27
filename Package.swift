// swift-tools-version:5.7
import PackageDescription
let package = Package(
    name: "VODUpload",
    platforms: [.iOS(.v12)],
    products: [.library(name: "VODUpload", targets: ["VODUpload", "VODUploadDependencies"])],
    dependencies: [.package(url: "https://github.com/AliOSStemp/AliyunOSSiOS.git", from: "2.11.0")],
    targets: [
        .binaryTarget(name: "VODUpload", url: "https://alivc-demo-cms.alicdn.com/versionProduct/sourceCode/upload/2.0.1/iOS/VODUpload.xcframework.zip", checksum: "01b3bcfa3741ae46164db95f43af035959d331238eefb5ca677ccdacbf400ca6"),
        .target(
            name: "VODUploadDependencies",
            dependencies: [.product(name: "AliyunOSSiOS", package: "AliyunOSSiOS")],
            path: "Sources/VODUploadDependencies",
            linkerSettings: [
                .linkedFramework("SystemConfiguration"),
                .linkedFramework("MobileCoreServices"),
                .linkedFramework("CoreMedia"),
                .linkedFramework("AVFoundation"),
                .linkedFramework("CoreTelephony"),
                .linkedFramework("Network"),
                .linkedLibrary("resolv")
            ]
        )
    ]
)
