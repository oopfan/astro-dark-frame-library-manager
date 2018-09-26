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

const fs = require('fs');
const readline = require('readline');

var asyncReadImageDir = (path) => {
  return new Promise((resolve, reject) => {
    fs.readdir(path, { withFileTypes: true }, (err, dirents) => {
      if (err) {
        reject(err);
      } else {
        var imageFileArray = [];
        dirents.forEach((dirent) => {
          if (dirent.isFile()) {
            const filePath = `${path}\\${dirent.name}`;
            const stats = fs.statSync(filePath);
            const birthTime = stats.birthtimeMs / 1000;
            imageFileArray.push({
              filePath,
              birthTime
            });
          }
        });
        resolve(imageFileArray);
      }
    });
  });
};

var asyncReadTemperatureLog = (path) => {
  return new Promise((resolve, reject) => {
    var unixtimeArray = [];
    var temperatureArray = [];
    var input = fs.createReadStream(path);
    input.on('error', function(err) {
      reject(err);
    });
    const rl = readline.createInterface({
      input,
      crlfDelay: Infinity
    });
    rl.on('line', (line) => {
      var parts = line.split(',');
      var unixtime = parts[0];
      var temperature = parts[2];
      if (+unixtime === +unixtime && +temperature === +temperature) {
        unixtimeArray.push(+unixtime);
        temperatureArray.push(+temperature);
      }
    });
    rl.on('close', () => {
      resolve({
        unixtimeArray,
        temperatureArray
      });
    });
  });
};

var lookupTemperatureIndex = (temperatureLog, unixtime) => {
  var index = temperatureLog.unixtimeArray.findIndex((element) => {
    return element > unixtime;
  });
  return index > 0 ? index - 1 : -1;
};

var mround = (number, multiple) => {
  return Math.round(number / multiple) * multiple;
};

module.exports = {
  asyncReadImageDir,
  asyncReadTemperatureLog,
  lookupTemperatureIndex,
  mround
};
