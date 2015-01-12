var cracklib = require('../build/Release/cracklib');

cracklib.checkPassword('somepassword', function (res) { console.log(res); });
