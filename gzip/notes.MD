# Project build steps

```
./bootstrap
bpc-translate generate-replacement --ignore --cc-override $(pwd)/bpc-gcc $(pwd)/gzip.toml /usr/bin/gcc $(pwd) -- ./configure
make
```

## Build file

[gzip.toml](gzip.toml)

# Translation steps

```
time ./bpc-translate translate -m /tmp/lifted -o /tmp/gzip -a /tmp/gzip-artifacts.zip  --model openai /home/coder/Documents/GitHub/gzip
```

<span style="color: red;">Currently troubleshooting this error: Failed to build source context from path `/home/coder/Documents/GitHub/cFS`. There is no `src/` directory like we expect. All the source is dumped into the top-level directory. </span>

# Results analysis and suggestions

details coming soon



