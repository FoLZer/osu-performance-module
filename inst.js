const path = require("path");
const fs = require("fs");
const os = require("os");

const p = path.resolve(".","src","osu-performance","dependencies","tinylogger","tinylogger","tinylogger.h");
const c = fs.readFileSync(p, { encoding: 'utf-8' });
fs.writeFileSync(p, c.replace(/ std::max/g, ' (std::max)'), { encoding: 'utf-8' });