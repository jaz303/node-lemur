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

module.exports = {
  getMidiOutputs: function() {
    return bindings.getMidiOutputs();
  },
  
  createMidiClient: function() {
    return bindings.createMidiClient();
  },
  
  createSession: function() {
    throw "wut!";
  }
}
