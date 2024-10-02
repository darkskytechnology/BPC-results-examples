# Project build steps

```
bpc-translate generate-replacement --cc-override $(pwd)/bpc-gcc $(pwd)/libmcs.toml /usr/bin/gcc $(pwd) -- ./configure --cross-compile $(pwd)/bpc-
make
```

# Translation steps

```
time ./bpc-translate translate -m /tmp/lifted -o /tmp/libmcs -a /tmp/libmcs-artifacts.zip  --model openai /home/coder/Documents/GitHub/libmcs
```

# Results analysis and suggestions

poor translation - more details coming soon



