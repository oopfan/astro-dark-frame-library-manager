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
    const rl = readline.createInterface({
      input: fs.createReadStream(path),
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
