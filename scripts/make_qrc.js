const fs = require('fs');
const os = require('os');
const path = require('path');


var qrc_path = null;
var file_path = null;
process.argv.forEach(function (val, idx, array) {
  if(idx == 2){ qrc_path = val;}
  if(idx == 3){ file_path = val;}
});
var basename = path.basename(file_path);
var abs_file_path = path.resolve(file_path);
///*
var out = fs.createWriteStream(qrc_path);
out.write("<!DOCTYPE RCC>"+os.EOL);
out.write('<RCC version="1.0">'+os.EOL);
out.write('<qresource>'+os.EOL);
out.write('<file alias="'+basename+'">'+abs_file_path+'</file>'+os.EOL);
out.write('</qresource>'+os.EOL);
out.write('</RCC>');
out.end();
//*/