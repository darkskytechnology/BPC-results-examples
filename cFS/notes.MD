# Project build steps

git submodule update --init
cp cfe/cmake/Makefile.sample Makefile
cp -r cfe/cmake/sample_defs sample_defs
bpc-translate generate-replacement --cc-override $(pwd)/bpc-gcc $(pwd)/cFS.toml /usr/bin/gcc $(pwd) -- make

## Build file

coming soon

# Translation steps

time ./bpc-translate translate -m /tmp/lifted -o /tmp/cFS -a /tmp/cFS-artifacts.zip  --model openai /home/coder/Documents/GitHub/cFS


# Results analysis and suggestions

details coming soon



