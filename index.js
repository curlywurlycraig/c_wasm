// Some learnings here from CNLohr's (very cool) rawdraw:
// https://github.com/cntools/rawdraw/blob/master/wasm/template.js
//
// Other helpful resources:
// https://depth-first.com/articles/2019/10/16/compiling-c-to-webassembly-and-running-it-without-emscripten/
// https://surma.dev/things/c-to-webassembly/
// https://ihsavru.medium.com/calling-javascript-code-from-c-c-using-webassembly-a9445c11bc6d
async function start() {
    // init webgl
    const canvas = document.querySelector("#canvas");
    const memoryText = document.querySelector("#memory");

    const gl = canvas.getContext("webgl");
    if (gl === null){
        console.error("Failed to init webgl.");
    }

    const memory = new WebAssembly.Memory({
        initial: 200
    });

    // Each HEAP is simply a different "view" into the memory.
    let HEAP8 = new Int8Array(memory.buffer);
    let HEAPU8 = new Uint8Array(memory.buffer);
    let HEAP16 = new Int16Array(memory.buffer);
    let HEAPU16 = new Uint16Array(memory.buffer);
    let HEAP32 = new Uint32Array(memory.buffer);
    let HEAPU32 = new Uint32Array(memory.buffer);
    let HEAPF32 = new Float32Array(memory.buffer);
    let HEAPF64 = new Float64Array(memory.buffer);

    let toUtf8Decoder = new TextDecoder( "utf-8" );
    function toUTF8(ptr) {
        // Remember, in C strings are null terminated strings.
        // Argument is a pointer to the first character.
        // Iterate and find null.
        // This is almost directly copied from rawdraw.
        let len = 0;
        for(let i = ptr; HEAPU8[i] != 0; i++) len++;
        return toUtf8Decoder.decode(HEAPU8.subarray(ptr, ptr+len));
    }

    function initShaderProgram(gl, vsSource, fsSource) {
        const vertexShader = loadShader(gl, gl.VERTEX_SHADER, vsSource);
        const fragmentShader = loadShader(gl, gl.FRAGMENT_SHADER, fsSource);

        const shaderProgram = gl.createProgram();
        gl.attachShader(shaderProgram, vertexShader);
        gl.attachShader(shaderProgram, fragmentShader);
        gl.linkProgram(shaderProgram);

        if (!gl.getProgramParameter(shaderProgram, gl.LINK_STATUS)) {
            // TODO Instead of console err, use a little debug textarea
            console.error('Unable to initialize the shader program: ', gl.getProgramInfoLog(shaderProgram));
            return null;
        }

        return shaderProgram;
    }

    // https://developer.mozilla.org/en-US/docs/Web/API/WebGL_API/Tutorial/Adding_2D_content_to_a_WebGL_context
    function loadShader(gl, type, source) {
        const shader = gl.createShader(type);
        gl.shaderSource(shader, source);
        gl.compileShader(shader);

        if (!gl.getShaderParameter(shader, gl.COMPILE_STATUS)) {
            alert('An error occurred compiling the shaders: ' + gl.getShaderInfoLog(shader));
            gl.deleteShader(shader);
            return null;
        }

        return shader;
    }

    const vsSource = `
    attribute vec4 aVertexPosition;

    uniform mat4 uModelViewMatrix;
    uniform mat4 uProjectionMatrix;

    void main() {
        gl_Position = uProjectionMatrix * uModelViewMatrix * aVertexPosition;
    }
    `;

    const fsSource = `
    void main() {
        gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);
    }
    `;

    const shaderProgram = initShaderProgram(gl, vsSource, fsSource);

    const glProgramInfo = {
        shaderProgram,
        attribLocations: {
            vertexPosition: gl.getAttribLocation(shaderProgram, 'aVertexPosition')
        },
        uniformLocations: {
            modelViewMatrix: gl.getUniformLocation(shaderProgram, 'uModelViewMatrix'),
            projectionMatrix: gl.getUniformLocation(shaderProgram, 'uProjectionMatrix')
        }
    };

    function initBuffers(gl) {
        const positionBuffer = gl.createBuffer();

        gl.bindBuffer(gl.ARRAY_BUFFER);

        // This array will come from C, soon
        const positions = [
            -1.0, 1.0,
            1.0, 1.0,
            -1.0, -1.0,
            1.0, -1.0
        ];


    }

    const imports = {
        env: {
            memory,
            prints: (ptr) => console.log(ptr, toUTF8(ptr)),
            printfl: (f) => console.log(f),
            glClear: (r, g, b, a) => {
                gl.clearColor(r, g, b, a);
                gl.clear(gl.COLOR_BUFFER_BIT);
            },
        }
    };

    const { instance } = await WebAssembly.instantiateStreaming(
        fetch('main.wasm'),
        imports
    );

    setInterval(() => {
        // set the text area contents
        let memoryString = "";
        HEAPU8
            .subarray(0, 256)
            .forEach((b, i) => {
                const nextPiece = (i+1) % 8 == 0
                    ? `${String(b)}\n`
                    : `${String(b)}\t`

                memoryString += nextPiece;
            });

        memoryText.value = memoryString
    }, 50);

    function iter() {
        // TODO, pass time since last iteration
        instance.exports.iter();

        window.requestAnimationFrame(iter);
    }

    window.requestAnimationFrame(iter);
}

window.onload = function() {
    start();
};
