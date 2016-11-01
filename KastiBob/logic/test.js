#!/mingw64/bin/node
var ip = "91.134.189.246";

var net = require('net');
var NodeRSA = require('node-rsa');

function toHexString(byteArray) {
  return byteArray.map(function(byte) {
    return ('0' + (byte & 0xFF).toString(16)).slice(-2);
  }).join('')
}
var client = new net.Socket();
var key = new NodeRSA();
key.importKey({
	n: new Buffer("109120132967399429278860960508995541528237502902798129123468757937266291492576446330739696001110603907230888610072655818825358503429057592827629436413108566029093628212635953836686562675849720620786279431090218017681061521755056710823876476444260558147179707119674283982419152118103759076030616683978566631413"),
	e: 65537,
	//d: new Buffer("3389")
}, 'components-public');
client.connect(7171, ip, function() {
	console.log(toHexString([0x61]));
	console.log('Connected');
	var p = new Uin8Array();
	//p.add_length();
	p.writeUInt8(0x01, p.length);
	p.writeUInt16(0x02, p.length);
	//p.buffer+=0x02;
	console.log(p);
	client.write(p);
});
client.on('data', function(data){
  console.log(data.toString());
});
client.on('end', function(){
  console.log('disconnected from server');
});
