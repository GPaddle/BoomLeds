const express = require('express');
const app = express();
const expressWs = require('express-ws')(app);

const port = 3000;

app.use(express.static('dist/'))

app.ws('/draw', function (ws, req) {
    ws.on('message', function (msg) {
        console.log(msg);
        // ws.send("response");
    });
});

app.listen(port, () => console.log(`Hosting: http://localhost:${port}!`))