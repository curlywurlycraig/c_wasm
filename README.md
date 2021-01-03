This is a basic project template for writing C code that builds to WASM.

It is a good starting point for a C WASM project without all the extras that come with Emscripten.

# Why C?

It's sort of fun, at least to me.

# Why not Emscripten?

Emscripten is useful for porting applications, or pretending that you're
writing a native C application.

I wanted to do away with the misdirection of faking things like OpenGL, and
wanted to know the real story, understanding how everything fits together.

Emscripten also pulls in a lot of extra stuff, and renders things like SVG
files or whatever by default. I wanted something lighter.

Most importantly, I wanted to explore how all this stuff fits together at a
lower level than Emscripten can provide (though it was helpful for poking
around the generated .js)

# Compiling

`make build`

# Running

Serve using something like Miniserve (`miniserve .`)
