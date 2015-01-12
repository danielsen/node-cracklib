var cracklib = require('../build/Release/cracklib');

cracklib.checkPassword('y0urpA55word', function (res) { console.log(res); });
