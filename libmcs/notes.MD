# Project source

https://gitlab.com/gtd-gmbh/libmcs

# Project build steps

```
bpc-translate generate-replacement --cc-override $(pwd)/bpc-gcc $(pwd)/libmcs.toml /usr/bin/gcc $(pwd) -- ./configure --cross-compile $(pwd)/bpc-
make
```

## Build file

[libmcs.toml](libmcs.toml)

# Translation steps

```
bpc-translate translate -m /home/ubuntu/tractor/lifted -o /home/ubuntu/translations/libmcs -a /home/ubuntu/artifacts/libmcs-artifacts.zip --model openai /home/ubuntu/targets/libmcs/libmcs.toml
```

# Results analysis and suggestions

First pass seems to be a poor translation. Some files are correct but many are way off. I'll explore to see where the issues are.



