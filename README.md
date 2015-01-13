node-cracklib - C++ binding to cracklib for checking password strength.

### Installing 

Note that this package requires that the cracklib development libraries 
be installed. Installation may vary on your system but, for example on CentOS:

    $yum install cracklib-devel

To install via nmp:
    
    $mkdir MyApplication
    $cd MyApplication
    $npm install cracklib

Or clone the repository and build from source:

    $git clone git@github.com:danielsen/node-cracklib.git
    $node-gyp configure -- -DMODULE\_NAME=cracklib -DBUILD_TARGET=/path/to/app
    $node-gyp build clean

### Usage

cracklib has two main access points: `fascistCheck(<password>)` and
`fascistCheckUser(<password>, <user>)`. Using `fascistCheck` will use the 
currently logged in user in the password check. `fascistCheckUser` allows 
for submission of an arbitrary user. This user need not be a valid user on 
your system, a phony username can be used, as can `null` or an empty string.

    var cracklib = require('cracklib');
    console.log(cracklib.checkPassword('pA5sword'));
    console.log(cracklib.checkPasswordUser('pA5sword', null));

### Response

The response to either function will be a simple dictionary response with a 
single memmber, "message". "message" will be a String if the
password check failed or Null if it passed.

    {
      "message": String | Null - Return value from the password check
    }

### Support

Please file bugs, issues, etc. at [https://github.com/danielsen/node-cracklib/issues].
