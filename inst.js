const path = require("path");
const fs = require("fs");
const os = require("os");

const p = path.resolve(".","src","osu-performance","dependencies","tinylogger","tinylogger","tinylogger.h");
const c = fs.readFileSync(p, { encoding: 'utf-8' });
fs.writeFileSync(p, c.replace(/ std::max/g, ' (std::max)'), { encoding: 'utf-8' });

if(!fs.existsSync("."+path.sep+"build")) {
    fs.mkdirSync("."+path.sep+"build");
    fs.mkdirSync("."+path.sep+"build"+path.sep+"Release");
}

if(os.platform() === "win32") {
    if(os.arch() === "x32") {
        fs.copyFileSync(path.resolve(".","src","osu-performance","dependencies","curl","dll","32bit","libcurl.dll"), path.resolve(".","build","Release","libcurl.dll"));
        fs.copyFileSync(path.resolve(".","src","osu-performance","dependencies","MySQL","dll","32bit","libmariadb.dll"), path.resolve(".","build","Release","libmariadb.dll"));
    } else {
        fs.copyFileSync(path.resolve(".","src","osu-performance","dependencies","curl","dll","64bit","libcurl.dll"), path.resolve(".","build","Release","libcurl.dll"));
        fs.copyFileSync(path.resolve(".","src","osu-performance","dependencies","MySQL","dll","64bit","libmariadb.dll"), path.resolve(".","build","Release","libmariadb.dll"));
    }
}
