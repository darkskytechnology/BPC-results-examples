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
bpc-translate translate -m /home/ubuntu/tractor/lifted -o /home/ubuntu/translations/libyaml -a /home/ubuntu/artifacts/libyaml-artifacts.zip --model openai /home/ubuntu/targets/libyaml/libyaml.toml
```

# Results analysis and suggestions

We are failing pretty hard on this because of the .h file being used by everything. In particular, our biggest issue is [here](https://github.com/yaml/libyaml/blob/840b65c40675e2d06bf40405ad3f12dec7f35923/include/yaml.h#L1790C1-L1790C18). 



