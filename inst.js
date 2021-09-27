const path = require("path");
const fs = require("fs");

const p = path.resolve(".","src","osu-performance","dependencies","tinylogger","tinylogger","tinylogger.h");
const c = fs.readFileSync(p, { encoding: 'utf-8' });
fs.writeFileSync(p.replace(/ std::max/g, ' (std::max)'), c, { encoding: 'utf-8' });