const WebSocket = require('ws');
const express = require('express');
const http = require('http');

const app = express();
const server = http.createServer(app);
const wss = new WebSocket.Server({ server });

app.use(express.static('.'));  // Serve your frontend files

wss.on('connection', function connection(ws) {
    console.log("New WebSocket connection established");

    ws.on('message', function incoming(message) {
        console.log('Received from Arduino: %s', message);
        // Broadcast this message to all connected WebSocket clients
        wss.clients.forEach(function each(client) {
            if (client.readyState === WebSocket.OPEN) {
                client.send(message);
            }
        });
    });
});

server.listen(8080, () => {
    console.log('Server started on http://localhost:8080');
});