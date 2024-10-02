# Project build steps

```autoreconf -fi
sudo apt install liburcu-dev libuv1-dev libcap-dev
bpc-translate generate-replacement --ignore --cc-override $(pwd)/bpc-gcc $(pwd)/bind9.toml /usr/bin/gcc $(pwd) -- ./configure --disable-doh
make
```

## Build file

coming soon

# Translation steps

```
time ./bpc-translate translate -m /tmp/lifted -o /tmp/bind9 -a /tmp/bind9-artifacts.zip  --model openai /home/coder/Documents/GitHub/bind9
```

# Results analysis and suggestions

coming soon



