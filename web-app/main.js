const express = require('express');
var app = express();
const bodyParser = require('body-parser')
const WebSocket = require('ws');

const wss = new WebSocket.Server({ port: 3001 });
var wssClient = []

const SMARTHOME_MODE = {
    mode_1 : {
        lampu_teras : 'OFF',
        lampu_ruangan : 'ON',
        tirai_jendela : 'TERBUKA',
        kipas_ac : 'ON',
        lampu_aquarium : 'ON',
        tv : 'OFF'
    },
    mode_2 : {
        lampu_teras : 'OFF',
        lampu_ruangan : 'ON_REDUP',
        tirai_jendela : 'TERTUTUP',
        kipas_ac : 'ON',
        lampu_aquarium : 'ON',
        tv : 'ON'
    },
    mode_3 : {
        lampu_teras : 'ON',
        lampu_ruangan : 'OFF',
        tirai_jendela : 'TERTUTUP',
        kipas_ac : 'OFF',
        lampu_aquarium : 'OFF',
        tv : 'OFF'
    }
}

wss.on('connection', function connection(ws) {
    wssClient.push(ws);
});

function broadcastMessage(message){
    for(var i=0; i<wssClient.length; i++){
        wssClient[i].send(JSON.stringify(message));
    }
}

app.use(bodyParser.json());
app.use('/static', express.static(__dirname + '/public'));

app.get('/', (req, res) => {
    res.sendFile(__dirname + '/', 'index.html');
})

app.post('/action', (req, res) => {
    var reqBody = req.body;
    if(reqBody.mode == 'mode_1'){
        broadcastMessage(SMARTHOME_MODE.mode_1);
    }
    else if(reqBody.mode == 'mode_2'){
        broadcastMessage(SMARTHOME_MODE.mode_2);
    }
    else if(reqBody.mode == 'mode_3'){
        broadcastMessage(SMARTHOME_MODE.mode_3);
    }
    res.status(200).send(JSON.stringify({
        status : 'success'
    }));
})

app.listen(8080, () => {
    console.log("Server listen on port 8080");
})