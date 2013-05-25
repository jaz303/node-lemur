var lemur = require('./index.js');

var client = lemur.createMidiClient();

console.log(client);

console.log(lemur.getMidiOutputs());

