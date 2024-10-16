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
bpc-translate translate -m /home/ubuntu/tractor/lifted -o /home/ubuntu/translations/gzip -a /home/ubuntu/artifacts/gzip-artifacts.zip --model openai /home/ubuntu/targets/gzip/gzip.toml 
```

coming soon

# Results analysis and suggestions

Currently failing because several files have dashes in their names which is failing when used as module names:

```
error: expected one of `;` or `{`, found `-`
 --> /home/ubuntu/translations/gzip/src/gnulib/lib/mod.rs:1:12
  |
1 | pub mod arg-nonnull_h;
  |            ^ expected one of `;` or `{`

```

I've opened an issue for this and will try just doing a blanket rename of the C code for now to bump past it.



