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
        // Iterate and find null.
        // This is almost directly copied from rawdraw.
        let len = 0;
        for(let i = ptr; HEAPU8[i] != 0; i++) len++;
        return toUtf8Decoder.decode(HEAPU8.subarray(ptr, ptr+len));
    }

    // This is also how Emscripten exposes "opengl" bindings
    const imports = {
        env: {
            memory,
            prints: (ptr) => console.log(ptr, toUTF8(ptr)),
            printfl: (f) => console.log(f),
            clearGl: (r, g, b, a) => {
                gl.clearColor(r, g, b, a);
                gl.clear(gl.COLOR_BUFFER_BIT);
            }
        }
    };

    const { instance } = await WebAssembly.instantiateStreaming(
        fetch('main.wasm'),
        imports
    );

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