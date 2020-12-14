var express = require('express');
var app = express();
var http = require('http');

app.use(express.json())
app.use(express.urlencoded({extended: true}))
app.use(express.static('images'));

app.head('/control', function(_, res) { // send control message to the esp8266
    var options = {
        host: 'ip_address_of_esp8266', // IP address of the esp8266
        port: '6666',
        method: 'HEAD'
    };

    callback = function(_) {}

    req = http.request(options, callback);
    req.end();

    req.on('error', (_) => {});

    res.sendStatus(200);
    console.log('command\'s been sent');
});

app.post('/control', function(req, res) {
    console.log(req.body);
    if (req.body.username === 'rs' && req.body.password === 'remoteswitch') {
        res.sendFile(__dirname + '/control.html');
    } else {
        res.redirect('/?ls=failed');
    }
})

app.get('/', function(_, res) {
    res.sendFile(__dirname + '/index.html');
});

app.get('*', function(_, res) {
    res.sendFile(__dirname + '/404.html');
});

app.listen(80, function() {
    console.log('listening on port 80');
});