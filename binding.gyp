{ 
  "targets": [
    {
      "target_name"   : "cracklib",
      "sources"       : [ "src/cracklib.cpp" ],
      "include_dirs"  : [ "<!(node -e \"require('nan')\")" ],
      "libraries"     : [ "-lcrack" ],
      "cflags"        : [ "-Wparentheses" ]
    }
  ]
}
