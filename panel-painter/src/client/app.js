const props = {
    panelWidth: 32,
    panelHeight: 8,
    borderWidth: 4,
    canvasMargin: 10, // if you change this also change in style.css for centering
};

const state = {
    cellSize: 0,
    canvasWidth: 0,
    canvasHeight: 0,
    panelData: [],
    lastX: -1,
    lastY: -1,
    color: "#ffff00",
    color2: "#000000",
    draw: true,
    ui: {
        canvas: undefined,
        colorPicker: undefined,
        resetButton: undefined,
        fillButton: undefined,
        clockButton: undefined,
        drawEraseButton: undefined,
        hueSlider: undefined,
        HueSliderText: undefined,
        textInput: undefined,
    }

};

function initialise() {

    document.getElementById("fillBucket").style.color = state.color;
    let windowWidth = parseInt(document.body.clientWidth);

    computeCellSize();

    let canvas = document.getElementById("canvas1");

    state.ui.canvas = canvas;

    state.canvasWidth = windowWidth;
    state.canvasHeight = windowWidth * (props.panelHeight / props.panelWidth);
    canvas.height = state.canvasHeight;
    canvas.width = state.canvasWidth;

    for (let x = 0; x < props.panelWidth; x++) {
        state.panelData[x] = [];
        for (let y = 0; y < props.panelHeight; y++) {
            state.panelData[x][y] = "#000000";
        }
    }

    state.ui.textInput = document.getElementById("inp");
    state.ui.textInput.addEventListener('input',textSend);

    state.ui.hueSlider = document.getElementById("HueSlider");
    state.ui.HueSliderText = document.getElementById("HueSliderText");
    state.ui.HueSliderText.innerText = "000";

    state.ui.drawEraseButton = document.getElementById("drawEraseButton");
    state.ui.drawEraseButton.addEventListener("click", changeDrawErase);

    document.getElementById("eraseLogo").style.display = "contents";

    state.ui.colorPicker = document.getElementById("colorPicker");
    state.ui.colorPicker.addEventListener("change", watchColorPicker, false);

    state.ui.fillButton = document.getElementById("fill");
    state.ui.fillButton.addEventListener("click", function () {
        fill(state.color);
    });
    state.ui.resetButton = document.getElementById("reset");
    state.ui.resetButton.addEventListener("click", function () {
        fill("#000000");
    });

    state.ui.canvas.addEventListener("mousedown", onMouseDown, false);

    state.ui.clockButton = document.getElementById("clock");
    state.ui.clockButton.addEventListener("click",clockApp);

    canvas.addEventListener("touchstart", touchStart, false);
    canvas.addEventListener("touchmove", touchMove, false);

    window.addEventListener("resize", reComputeSize);

    reComputeSize();
    draw();
}

function computeCellSize() {
    let windowWidth = parseInt(document.body.clientWidth);

    state.cellSize = windowWidth - 2 * props.canvasMargin;
    state.cellSize -= (props.borderWidth * (props.panelWidth + 1));
    state.cellSize /= props.panelWidth;
    state.cellSize = parseInt(state.cellSize);
}

function changeDrawErase() {

    state.draw = !state.draw;

    //drawing mode
    if (state.draw) {

        console.log(state.color + " c1|c2 " + state.color2);
        let c = state.color;
        console.log(state.color + " c1|c2 " + state.color2);
        state.color = state.color2;
        console.log(state.color + " c1|c2 " + state.color2);
        state.color2 = "#000000";
        console.log(state.color + " c1|c2 " + state.color2);


        document.getElementById("eraseLogo").style.display = "contents";
        document.getElementById("drawLogo").style.display = "none";

        //erasing mode
    } else {

        console.log(state.color + " c1|c2 " + state.color2);
        state.color2 = state.color;
        console.log(state.color + " c1|c2 " + state.color2);
        state.color = "#000000";
        console.log(state.color + " c1|c2 " + state.color2);

        document.getElementById("drawLogo").style.display = "contents";
        document.getElementById("eraseLogo").style.display = "none";

    }

}

function reComputeSize() {

    let windowWidth = parseInt(document.body.clientWidth);
    computeCellSize();

    state.canvasWidth = windowWidth;
    state.canvasHeight = windowWidth * (props.panelHeight / props.panelWidth);

    let canvas = document.getElementById("canvas1");
    canvas.height = state.canvasHeight;
    canvas.width = state.canvasWidth;

    draw();

}

function fill(color) {
    let r = parseInt(color.substring(1, 3), 16);
    let g = parseInt(color.substring(3, 5), 16);
    let b = parseInt(color.substring(5, 7), 16);

    for (let x = 0; x < props.panelWidth; x++) {
        for (let y = 0; y < props.panelHeight; y++) {
            if (state.panelData[x][y] != color) {
                state.panelData[x][y] = color;
            }
        }

    }

    sendData(5, 0, 0, r, g, b);

    draw();
}

function watchColorPicker(event) {
    state.color = event.target.value;
    document.getElementById("fillBucket").style.color = state.color;
}

function setColor(e) {
    let value = state.ui.hueSlider.value;
    console.log(value);
    state.ui.HueSliderText.innerText = value;
    let color = hslToRgb(value / 360, 1.00, 0.50);

    let r = color[0].toString(16);
    let g = color[1].toString(16);
    let b = color[2].toString(16);

    if (r.length == 1) {
        r = "0" + r;
    }
    if (g.length == 1) {
        g = "0" + g;
    }
    if (b.length == 1) {
        b = "0" + b;
    }


    state.color = "#" + r + g + b;
    console.log(state.color);
}

/**
 * Converts an HSL color value to RGB. Conversion formula
 * adapted from http://en.wikipedia.org/wiki/HSL_color_space.
 * Assumes h, s, and l are contained in the set [0, 1] and
 * returns r, g, and b in the set [0, 255].
 *
 * @param   {number}  h       The hue
 * @param   {number}  s       The saturation
 * @param   {number}  l       The lightness
 * @return  {Array}           The RGB representation
 */
function hslToRgb(h, s, l) {
    var r, g, b;

    if (s == 0) {
        r = g = b = l; // achromatic
    } else {
        var hue2rgb = function hue2rgb(p, q, t) {
            if (t < 0) t += 1;
            if (t > 1) t -= 1;
            if (t < 1 / 6) return p + (q - p) * 6 * t;
            if (t < 1 / 2) return q;
            if (t < 2 / 3) return p + (q - p) * (2 / 3 - t) * 6;
            return p;
        };

        var q = l < 0.5 ? l * (1 + s) : l + s - l * s;
        var p = 2 * l - q;
        r = hue2rgb(p, q, h + 1 / 3);
        g = hue2rgb(p, q, h);
        b = hue2rgb(p, q, h - 1 / 3);
    }

    return [Math.round(r * 255), Math.round(g * 255), Math.round(b * 255)];
}

function touchStart(e) {
    getTouchPos(e);
    event.preventDefault();
}

function touchMove(e) {
    getTouchPos(e);
    event.preventDefault();
}

function getTouchPos(event) {
    var e;
    if (!e)
        e = event;

    if (e.touches) {
        if (e.touches.length == 1) {
            var touch = e.touches[0];


            var touchX = touch.pageX - props.canvasMargin;
            var touchY = touch.pageY - props.canvasMargin;

            processingCoords(touchX, touchY);
        }
    }
}

function onMouseDown(event) {

    function onMouseMove(event) {
        var canvasX = event.pageX - props.canvasMargin;
        var canvasY = event.pageY - props.canvasMargin;

        processingCoords(canvasX, canvasY);
    }

    function onMouseUp(event) {
        document.removeEventListener("mousemove", onMouseMove);
        document.removeEventListener("mouseup", onMouseUp);
    }
    document.addEventListener("mousemove", onMouseMove);
    document.addEventListener("mouseup", onMouseUp);
}


/**
 * 
 * Codes :
 * 1 Display
 * 2 Image
 * 3 Pixel
 * 4 Text
 * 5 Fill
 */
function sendData(type, x, y, r, g, b) {
    try {

        if (webSocket.readyState === webSocket.OPEN) {

            if (type == 1) {
                webSocket.send(JSON.stringify([type, 0, 0, 0, 0, 0]));
            } else if (type == 4){
                webSocket.send(JSON.stringify([type, x, y, r, 0, 0]));
            }else {

                let color = state.panelData[x][y];

                let r1 = color.r;
                let g1 = color.g;
                let b1 = color.b;
                if (r != r1 || g != g1 || b != b1) {
                    webSocket.send(JSON.stringify([type, x, y, r, g, b]));
                }

            }
        }

    } catch (error) {
        console.log("WebSocket problem");
    }

}

function draw() {

    state.ui.canvas = document.getElementById("canvas1").getContext("2d");
    document.getElementById("canvas1").background = "f00000";
    state.ui.canvas.fillStyle = "#f00000";
    state.ui.canvas.fill();

    //    console.log(state.canvasHeight);

    for (let x = 0; x < props.panelWidth; x++) {
        for (let y = 0; y < props.panelHeight; y++) {
            state.ui.canvas.fillStyle = state.panelData[x][y];
            state.ui.canvas.fillRect((state.cellSize + props.borderWidth) * x,
                (state.cellSize + props.borderWidth) * y,
                state.cellSize,
                state.cellSize);
        }
    }
}

function processingCoords(x, y) {
    if (x >= 0 && x <= state.canvasWidth && y >= 0 && y <= state.canvasHeight) {

        let targetX = parseInt(x / (state.cellSize + props.borderWidth) / 1);
        let targetY = parseInt(y / (state.cellSize + props.borderWidth) / 1);

        if (state.color != state.panelData[targetX][targetY]) {
            state.panelData[targetX][targetY] = state.color;
            //console.log(state.color);
            let r = parseInt(state.color.substring(1, 3), 16);
            let g = parseInt(state.color.substring(3, 5), 16);
            let b = parseInt(state.color.substring(5, 7), 16);

            sendData(3, targetX, targetY, r, g, b);

        }
        draw();
    }
}

function readURL(input) {
    if (input.files && input.files[0]) {
        let reader = new FileReader();
        reader.onload = function (e) {
            let img = document.getElementById('source');
            img.src = e.target.result;
            //            img.width = 320;
            //            img.height = 80;

        };
        reader.readAsDataURL(input.files[0]);

        let canvas = document.getElementById('canvasTmp');
        let ctx = canvas.getContext('2d');

        let image = document.getElementById("source");

        image.onload = function () {

            let w = image.width;
            let h = image.height;

            //canvas.style.width = w;
            //canvas.style.height = h;
            let ctx = canvas.getContext('2d');
            ctx.drawImage(image, 0, 0);


            let canvas2 = document.getElementById("canvas2");
            let ctx2 = canvas2.getContext('2d');

            canvas2.width = 10 * w;
            canvas2.height = 10 * h;

            //alert(canvas2.width);

            ctx2.fillStyle = "white";
            ctx2.fillRect(0, 0, canvas2.width, canvas2.height);
            fill("#000000");

            let xMax = Math.min(image.width, 32);
            let yMax = Math.min(image.height, 8);

            for (let x = 0; x < xMax; x++) {
                for (let y = 0; y < yMax; y++) {
                    let data = ctx.getImageData(x, y, 1, 1);

                    let couleur = "#" + data.data[0].toString(16) +
                        data.data[1].toString(16) +
                        data.data[2].toString(16);
                    ctx2.fillStyle = couleur;

                    ctx2.fillRect(x * 10, y * 10, 10, 10);

                    if (couleur != state.panelData[x][y]) {
                        state.panelData[x][y] = couleur;
                        //console.log(state.color);
                        let r = data.data[0];
                        let g = data.data[1];
                        let b = data.data[2];
                        sendData(2, x, y, r, g, b);
                    }
                    draw();
                }
            }
            sendData(1, 0, 0, 0, 0, 0);

        };
    }
}

function clockApp(){
    sendData(6,0,0,"clock",0,0);
}

function textSend(event){

    let txt = state.ui.textInput.value;
    console.log(txt);
    sendData(4,0,7,txt,0,0);

}


let wsUrl = window.location.protocol === "https:" ? "wss://" : "ws://";
wsUrl += window.location.host;
wsUrl += window.location.host.endsWith(":3000") ? "" : ":81";
wsUrl += window.location.pathname;
wsUrl += "draw";

console.log("WebSocket to", wsUrl);
const webSocket = new WebSocket(wsUrl);