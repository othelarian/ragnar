{
  "targets": [
    {
      "target_name": "ragnar",
      "sources": ["src/ragnar.cc"],
      "cflags": ["-pedantic","-Wall"],
      "link_settings": {
        "libraries": ["-lX11","-lXinerama"]
      }
    }
  ]
}
