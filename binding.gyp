{
  "targets": [
    {
      "target_name": "ragnar",
      "sources": [
        "src/ragnar_node.cc",
        "src/ragnar.cc"
      ],
      "include_dirs": ["<!(node -e \"require('nan')\")"],
      "link_settings": {
        "libraries": ["-lxcb","-lxcb-randr"]
      },
      "conditions": [
        ['OS=="mac"', {
          "include_dirs": ["/opt/X11/include"],
          "library_dirs": ["/opt/X11/lib"]
        }]
      ]
    }
  ]
}
