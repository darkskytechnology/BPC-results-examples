# Project source

https://github.com/yaml/libyaml

# Project build steps

```
bpc-translate generate-replacement --ignore --cc-override $(pwd)/bpc-gcc $(pwd)/libyaml.toml /usr/bin/gcc $(pwd) -- ./configure
make -C src
```

## Build file

[libyaml.toml](libyaml.toml)

# Translation steps

```
time ./bpc-translate translate -m /tmp/lifted -o /tmp/libyaml -a /tmp/libyaml-artifacts.zip  --model openai /home/coder/Documents/GitHub/libyaml
```

# Results analysis and suggestions

coming soon



