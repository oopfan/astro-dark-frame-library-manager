/*
Copyright 2018 Brian D. Morgan

Permission to use, copy, modify, and/or distribute this software for any purpose with
or without fee is hereby granted, provided that the above copyright notice and this
permission notice appear in all copies.

THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH REGARD
TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS.
IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR
CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE,
DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS
ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/

const yargs = require('yargs');
const utils = require('./utils.js');

const imageinOptions = {
  describe: 'The path name of the input image file directory.',
  demand: true,
  alias: 'in'
};

const tempinOptions = {
  describe: 'The path name of the input temperature log file.',
  demand: true,
  alias: 'log'
};

const imageoutOptions = {
  describe: 'The path name of the parent output image file directory containing child temperature directories.',
  demand: true,
  alias: 'out'
};

const argv = yargs
  .command('list-images', 'Read the input image directory and list the file names and creation date.', {
    imagein: imageinOptions
  })
  .command('list-temps', 'Read the temperature log file and list the time and temperature.', {
    tempin: tempinOptions
  })
  .command('organize', 'For each image file, look up the temperature, and list the command shell "move" command.', {
    imagein: imageinOptions,
    tempin: tempinOptions,
    imageout: imageoutOptions
  })
  .help()
  .argv;

var command = argv._[0];

if (command == 'list-images') {
  utils.asyncReadImageDir(argv.imagein).then((imageFileArray) => {
    console.log('path,birthtime');
    imageFileArray.forEach((imageFile) => {
      console.log(`${imageFile.filePath},${imageFile.birthTime}`);
    });
  }, (reason) => {
    console.log(reason);
  });
} else if (command == 'list-temps') {
  utils.asyncReadTemperatureLog(argv.tempin).then((temperatureLog) => {
    console.log('unixtime, tempF');
    const len = temperatureLog.unixtimeArray.length;
    for (var index = 0; index < len; index++) {
      console.log(`${temperatureLog.unixtimeArray[index]},${temperatureLog.temperatureArray[index]}`);
    }
  }, (reason) => {
    console.log(reason);
  });
} else if (command == 'organize') {
  Promise.all([
    utils.asyncReadTemperatureLog(argv.tempin),
    utils.asyncReadImageDir(argv.imagein)
  ]).then((resultArray) => {
    var temperatureLog = resultArray[0];
    var imageFileArray = resultArray[1];
    imageFileArray.forEach((element) => {
      var filePath = element.filePath;
      var birthTime = element.birthTime;
      var index = utils.lookupTemperatureIndex(temperatureLog, birthTime);
      if (index >= 0) {
        var number = temperatureLog.temperatureArray[index];
        var rounded = utils.mround(number, 0.5);
        console.log(`MOVE "${filePath}" "${argv.imageout}\\temp_${rounded.toFixed(1)}F\\"`);
      } else {
        console.log(`REM -- Temperature Not Found -- ${filePath}`);
      }
    });
  }, (reason) => {
    console.log(reason);
  });
} else {
  console.log(`Unknown command: ${command}`);
}
