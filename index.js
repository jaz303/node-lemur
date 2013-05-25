var bindings = require("bindings")("lemur_bindings.node");

var NOTE_NAMES = {
  'C'   : 0,
  'C#'  : 1,
  'Db'  : 1,
  'D'   : 2,
  'D#'  : 3,
  'Eb'  : 3,
  'E'   : 4,
  'F'   : 5,
  'F#'  : 6,
  'Gb'  : 6,
  'G'   : 7,
  'G#'  : 8,
  'Ab'  : 8,
  'A'   : 9,
  'A#'  : 10,
  'Bb'  : 10,
  'B'   : 11
};

var NOTES = {};

var note = 0;
for (var octave = 0; octave < 12; octave++) {
  for (var noteName in NOTE_NAMES) {
    var noteNumber = (12 * octave) + NOTE_NAMES[noteName];
    if (noteNumber <= 127) {
      NOTES[noteName + octave] = noteNumber;
    }
  }
}

// 3 bytes
function noteOff(channel, note, velocity) {
  return 0x800000 | ((channel - 1) << 16) | (NOTES[note] << 8) | velocity;
}

// 3 bytes
function noteOn(channel, note, velocity) {
  return 0x900000 | ((channel - 1) << 16) | (NOTES[note] << 8) | velocity;
}

// 3 bytes
function aftertouch(channel, note, velocity) {
  return 0xA00000 | ((channel - 1) << 16) | (NOTES[note] << 8) | velocity;
}

// 3 bytes
function controlChange(channel, controller, value) {
  return 0xB00000 | ((channel - 1) << 16) | (controller << 8) | value;
}

// 2 bytes
function programChange(channel, program) {
  return 0xC000 | ((channel - 1) << 16) | program;
}

// 2 bytes
function channelAftertouch(channel, value) {
  return 0xD000 | ((channel - 1) << 16) | program;
}

// 3 bytes
// TODO: value is 14 bit. might be more sensible to map it to range (-1.0,1.0)
function pitchWheel(channel, value) {
  return 0xE00000 | ((channel - 1) << 16) | ((value & 0x7F) << 8) | ((value >> 7) & 0x7F);
}

module.exports = {
  getMidiOutputs: function() {
    return bindings.getMidiOutputs();
  },
  
  createMidiClient: function() {
    return bindings.createMidiClient();
  },
  
  createSession: function() {
    throw "wut!";
  },
  
  noteOn: noteOn,
  noteOff: noteOff
}
