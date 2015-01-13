var cracklib = require('../build/Release/cracklib');

console.log(cracklib.fascistCheck('y0urpA55word'));
console.log(cracklib.fascistCheck('pA55word'));
console.log(cracklib.fascistCheckUser('pA55word', 'pmta'));
console.log(cracklib.fascistCheckUser('y0urpA55word', null));
