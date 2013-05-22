var bindings = require("bindings")("lemur_bindings.node");

module.exports = {
  getMidiOutputs: function() {
    return bindings.getMidiOutputs();
  },
  
  createSession: function() {
    throw "wut!";
  }
}
