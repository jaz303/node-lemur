//var binding = require('./build/Release/lemur.node');

try {
  module.exports = require('./build/Release/bindings');
} catch (e) {
  module.exports = require('./build/Debug/bindings');
}
