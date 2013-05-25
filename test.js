var lemur = require('./index.js');

var output = lemur.getMidiOutputs()[0];
var client = lemur.createMidiClient();

// 0x90   Note on, channel 1
// 0x45   Middle A (MIDI note #69)
// 0x40   Velocity 64
client.send(output, lemur.noteOn(1, 'C4', 100));

// 0x80   Note off, channel 1
// 0x45   Middle A (MIDI note #69)
// 0x40   Velocity 64
setTimeout(function() { client.send(output, lemur.noteOff(1, 'C4', 64)); }, 2000);
