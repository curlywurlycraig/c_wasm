build:
	clang \
		--target=wasm32 \
		--no-standard-libraries \
		-fno-builtin \
		-fno-exceptions \
		-Wl,--export-all \
		-Wl,--no-entry \
		-Wl,--allow-undefined \
		-Wl,--import-memory \
		-o main.wasm \
		main.c
