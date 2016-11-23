var http = require('http');
var url = require('url');
var ffi = require('node-ffi');
var ref = require('ref');

var gnode = new ffi.Library("bin/libgnode", {
	'GN_prepare_light_sensor': [ 'int', [ ] ],
	'GN_get_light_sensor': [ 'int', [ ] ],
	'GN_release_light_sensor': [ 'void', [ ] ],
        'GN_prepare_leds': [ 'int', ['int', 'int' ] ],
        'GN_get_led': [ 'int', ['int' ] ],
        'GN_set_led': [ 'int',  ['int', 'int' ] ],
        'GN_release_led':[ 'void', ['int' ] ],
	'GN_prepare_thermistor': [ 'int', [ ] ],
	'GN_get_thermistor': [ 'float', [ ] ],
	'GN_release_thermistor': [ 'void', [ ] ],
	'GN_prepare_servo' : [ 'int', [ 'int', 'int', 'int' ] ],
	'GN_enable_servo' : [ 'int', [ 'int' ] ],
	'GN_disable_servo' : [ 'int', [ 'int' ] ]
});

gnode.GN_prepare_light_sensor();
gnode.GN_prepare_leds(16, 0);

server = http.createServer(function (req, res) {
  var action, urlData, user;
  urlData = url.parse(req.url, true);
  action = urlData.pathname;
  res.writeHead(200, {'Content-Type': 'text/plain'});
  if (action === "/lightsensor"){
      return res.end("Light Sensor reads: " + gnode.GN_get_light_sensor());
  }else if (action === "/ledon"){
      console.log('Turn on LED');
      gnode.GN_set_led(16,1);
      //return res.end("Turn on LED: " + gnode.GN_set_led(16,1));
  }else if (action === "/ledoff"){
      console.log('Turn off LED');
      gnode.GN_set_led(16,0);
      //return res.end("Turn off LED: " + gnode.GN_set_led(16,0));
  }else if (action === "/opendoor"){
      console.log('Open Door');
      //Need to check values, try channel 1 only
      gnode.GN_set_led(16,1);
      gnode.GN_prepare_servo(1, 50000000, 1900000);
      gnode.GN_enable_servo(1); 
      gnode.GN_disable_servo(1);
      //return res.end("Turn off LED: " + gnode.GN_set_led(16,0));
  }else if (action === "/closedoor"){
      console.log('Close Door');
      //Need to check values, try channel 1 only
      gnode.GN_set_led(16,0);
      gnode.GN_prepare_servo(1, 50000000, 2500000);
      gnode.GN_enable_servo(1); 
      gnode.GN_disable_servo(1);
      //return res.end("Turn off LED: " + gnode.GN_set_led(16,0));
  }else{
      return res.end("<h1> Welcome to Galileo board Node.js server</h1>");
  }
});
server.listen(1337);
console.log('Node server is running, current time is ' + new Date());
//gnode.GN_release_led(16);
gnode.GN_release_light_sensor();
