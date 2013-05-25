var lemur = require('./index.js');

var output = lemur.getMidiOutputs()[0];
var client = lemur.createMidiClient();

client.send(output, 0x904540);
setTimeout(function() { client.send(output, 0x804540); }, 2000);
