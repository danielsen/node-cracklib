{ 
  "targets": [
    {
      "target_name" : "cracklib",
      "sources"     : [ "src/cracklib.cpp" ],
      "libraries"   : [ "-lcrack" ],
      "cflags"      : [ "-Wparentheses" ]
    },
    { 
      "target_name"   : "action_after_build",
      "type"          : "none",
      "dependencies"  : [ "<(MODULE_NAME)" ],
      "copies"        : [ {
        "files"       :  [ "<(module_root_dir)/build/Release/cracklib.node" ],
        "destination" : "<(BUILD_TARGET)/node_modules/"
      }]
    }
  ]
}
