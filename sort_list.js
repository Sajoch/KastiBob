var fs = require("fs");
var list = fs.readFileSync("list");
var tab = list.toString().split('\r\n');
var obj = [];
for(var t=0;t<tab.length;t+=2){
	var name = new RegExp("(.*)\"(.*)\"").exec(tab[t])[2];
	var o = [name, tab[t], tab[t+1]];
	obj.push(o);
}
obj.sort(function(a, b){
	if(a[0] < b[0]) return -1;
  if(a[0] > b[0]) return 1;
  return 0;
});
var txt = "";
for(var t in obj){
	txt+=obj[t][1]+"\r\n";
	txt+=obj[t][2]+"\r\n";
}
fs.writeFileSync("list", txt);