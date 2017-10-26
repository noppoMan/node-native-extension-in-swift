{
  "targets": [
    {
      "target_name": "swift",
      "sources": ["swift.cc"],
      "include_dirs": [
        "<!(node -e \"require('nan')\")"
      ]
    }
  ]
}
