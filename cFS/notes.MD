# Project source

https://github.com/nasa/cFS

# Project build steps

```
git submodule update --init
cp cfe/cmake/Makefile.sample Makefile
cp -r cfe/cmake/sample_defs sample_defs
bpc-translate generate-replacement --cc-override $(pwd)/bpc-gcc $(pwd)/cFS.toml /usr/bin/gcc $(pwd) -- make
```

## Build file

[cFS.toml](cFS.toml)

# Translation steps

```
bpc-translate translate -m /home/ubuntu/tractor/lifted -o /home/ubuntu/translations/cFS -a /home/ubuntu/artifacts/cFS-artifacts.zip --model openai /home/ubuntu/targets/cFS/cFS.toml
```

# Results analysis and suggestions

details coming soon



