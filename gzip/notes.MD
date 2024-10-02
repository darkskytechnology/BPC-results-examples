# Project build steps

./bootstrap
bpc-translate generate-replacement --ignore --cc-override $(pwd)/bpc-gcc $(pwd)/gzip.toml /usr/bin/gcc $(pwd) -- ./configure
make

## Build file

coming soon

# Translation steps

time ./bpc-translate translate -m /tmp/lifted -o /tmp/gzip -a /tmp/gzip-artifacts.zip  --model openai /home/coder/Documents/GitHub/gzip


# Results analysis and suggestions

details coming soon



