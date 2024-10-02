# Project build steps

```
bpc-translate generate-replacement --cc-override $(pwd)/bpc-gcc $(pwd)/libmcs.toml /usr/bin/gcc $(pwd) -- ./configure --cross-compile $(pwd)/bpc-
make
```

## Build file

[libmcs.toml](libmcs.toml)

# Translation steps

```
time ./bpc-translate translate -m /tmp/lifted -o /tmp/libmcs -a /tmp/libmcs-artifacts.zip  --model openai /home/coder/Documents/GitHub/libmcs
```

# Results analysis and suggestions

First pass seems to be a poor translation. Some files are correct but many are way off. I'll explore to see where the issues are.



