// THIS IS COMMENTED OUT BECAUSE WE MOVED THE LOGIC TO: pacman.js
// // Import the WebSocket library
// const WebSocket = require('ws');

// // const serverAddress = 'ws://localhost:3000';
// const serverAddress = 'ws://localhost:8080'; // address is 8080 on pi
// const connection = new WebSocket(serverAddress);

// connection.onopen = () => {
//     console.log('WebSocket connection established');
// };

// connection.onerror = (error) => {
//     console.error('WebSocket Error:', error);
// };

// connection.onmessage = (e) => {
//     console.log('Input from Arduino:', e.data);
//     updateGame(e.data);  // Update game based on input
// };

// function updateGame(input) {
//     // Implement game logic here based on the input from the controller
//     movePacman(1)
//     console.log("TODO: SHOULD MOVE PACMAN IN THIS FUNCTION")
// }