const path = require('path');
const webpack = require('webpack');

module.exports = {
  entry: {
  	particles: ['./lib/js/src/index.js'],
  },
  output: {
    path: path.join(__dirname, "public"),
    filename: '[name].js',
  },
};
