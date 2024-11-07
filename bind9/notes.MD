# Project source

https://github.com/isc-projects/bind9

# Project build steps

```
autoreconf -fi
sudo apt install liburcu-dev libuv1-dev libcap-dev
bpc-translate generate-replacement --ignore --cc-override $(pwd)/bpc-gcc $(pwd)/bind9.toml /usr/bin/gcc $(pwd) -- ./configure --disable-doh
make
```

## Build file

[bind9.toml](bind9.toml)


# Translation steps

```
bpc-translate translate -m /home/ubuntu/tractor/lifted -o /home/ubuntu/translations/bind9 -a /home/ubuntu/artifacts/bind9-artifacts.zip --model openai /home/ubuntu/targets/bind9/bind9.toml 
```

# Results analysis and suggestions

Failed to produce code structure due to confusion over directory named lib and crate lib produced by Bulletproof Code. Translation proceeded following manual renaming but failed frequently due to missing global context and missing training data. Best results were observed for single targets within `/bin/tools`.  


