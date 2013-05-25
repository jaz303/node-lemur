var bindings = require("bindings")("lemur_bindings.node");

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
