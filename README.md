node-cracklib - C++ binding to cracklib for checking password strength.

### Installing 

Note that this package requires that the cracklib development libraries 
be installed. Installation may vary on your system but, for example on CentOS:

    $yum install cracklib-devel

To install via nmp:
    
    $mkdir MyApplication
    $cd MyApplication
    $npm install node-cracklib

Or clone the repository and build from source:

    $git clone git@github.com:danielsen/node-cracklib.git
    $node-gyp configure -- -DMODULE\_NAME=cracklib -DBUILD_TARGET=/path/to/app
    $node-gyp build clean

### Usage

    var cracklib = require('cracklib');
    cracklib.checkPassword('mypassword', function (res) { console.log(res) });

### Response

The callback to checkPassword() should be able to handle a simple dictionary
response with a single memmber, "message". "message" will be a String if the
password check failed or Null if it passed.

    {
      "message": String | Null - Return value from the password check
    }
