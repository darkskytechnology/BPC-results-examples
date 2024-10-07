# Project source

https://savannah.gnu.org/git/?group=gzip

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
time bpc-translate translate -m /tmp/lifted -o /tmp/gzip -a /tmp/gzip-artifacts.zip  --model openai /home/coder/Documents/GitHub/gzip/gzip.toml
```

coming soon

# Results analysis and suggestions

details coming soon



