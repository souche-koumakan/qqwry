{
  "targets": [{
    "target_name": "qqwry",
    "sources": [
      "./src/qqwry.cc",
      "./src/addon.cc"
    ],
    "include_dirs": [
      "./src/libqqwry",
      "<!(node -e \"require('nan')\")"
    ],
    "dependencies": [
      "libqqwry"
    ]
  }, {
    "target_name": "libqqwry",
    "sources": [
      "./src/libqqwry/qqwry.c"
    ],
    "target_type": "static_library"
  }]
}
