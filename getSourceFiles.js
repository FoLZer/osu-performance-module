const fs = require('fs');
const path = require('path');

function walk(dir) {
    const results = [];
    const list = fs.readdirSync(dir);
    let pending = list.length;
    if (!pending) return results;
    for(const file of list) {
        const f = dir + path.sep + file;
        const stat = fs.statSync(f);
        if(file.includes("test") || file === "examples") {
            if(!--pending) return results;
            continue;
        }
        if(stat && stat.isDirectory()) {
            const res = walk(f);
            results.push(...res);
            if(!--pending) return results;
        } else {
            results.push(f.substring(2));
            if(!--pending) return results;
        }
    }
}

module.exports = { walk };