
const path = require ("node:path");

const addon = require (path.resolve(__dirname, "../build/Release/naph.node"));

module.exports = addon;
