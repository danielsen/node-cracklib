node-cracklib - C++ binding to cracklib for checking password strength.

### Installing 

Note that this package requires that the cracklib development libraries are installed. Installation may vary on your system but, for example on CentOS:

    $ yum install cracklib-devel

To install via npm:
    
    $ npm install cracklib

Or clone the repository and build from source:

    $ git clone git@github.com:danielsen/node-cracklib.git
    $ node-gyp configure -- -DMODULE_NAME=cracklib -DBUILD_TARGET=/path/to/app
    $ node-gyp build clean

### Usage

cracklib has two main access points: `fascistCheck(password[, dictionaryPath])` and `fascistCheckUser(password, user[, dictionaryPath])`. Using `fascistCheck` uses the currently logged in user in the password check. `fascistCheckUser` allows for submission of an arbitrary user. This user need not be a valid user on your system, a phony username can be used, as can `null` or an empty string. Both methods support custom dictionaries using the optional `dictionaryPath` argument. If they argument is left undefined the default dictionary is used.

    let cracklib = require('cracklib');
    console.log(cracklib.fascistCheck('pA5sword'));
    console.log(cracklib.fascistCheckUser('pA5sword', null));

### Response

The response to either function is a simple dictionary response with a single member, `message`. `message` is a String if the password check failed or Null if it passed.

    {
      "message": String | Null - Return value from the password check
    }

### Support

Please file bugs, issues, etc. at https://github.com/danielsen/node-cracklib/issues. PRs for bug fixes are welcome.

### Development

If you want to hack on this code you'll need to make sure that the following are installed on your system:

- NodeJs development libraries
- Cracklib development libraries
- node-gyp

#### Clone and Build

    $ git clone git@github.com:danielsen/node-cracklib.git
    $ node-gyp configure -- -DMODULE_NAME=cracklib -DBUILD_TARGET=/path/to/app
    $ node-gyp build