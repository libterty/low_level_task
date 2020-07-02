var module;

if (process.env.DEBUG) {
    module = require('./build/Debug/module.node');
} else {
    module = require('./build/Release/module.node');
}

module.exports = module;