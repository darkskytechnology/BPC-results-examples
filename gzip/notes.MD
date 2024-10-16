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

Currently failing because MANY files have dashes in their names which is not allowed in Rust. Remarkably we've never encountered this before.

```
error: expected one of `;` or `{`, found `-`
 --> /home/ubuntu/translations/gzip/src/gnulib/lib/mod.rs:1:12
  |
1 | pub mod arg-nonnull_h;
  |            ^ expected one of `;` or `{`

```

I've opened an issue for this in BPC. However, for now, I am just going to use a simple work-around using a script to rename these files (there are hundreds) and fix up all their references (there are thousands).

```
#!/bin/bash


SAVEIFS=$IFS
IFS=$(echo -en "\n\b")

# Step 1: Find all files with a dash in their name
files_with_dash=$(find . -type f -name "*-*")

declare -A rename_map

# Step 2: Rename the files and record old/new names
for file in $files_with_dash; do
  # Construct new filename (replace dash with underscore)
  new_file=$(echo "$file" | sed 's/-/_/g')

  # Rename the file
  echo "Renaming $file to $new_file"
  mv "$file" "$new_file"

  # Store in rename_map
  rename_map["$(basename "$file")"]="$(basename "$new_file")"
done

# Step 3: Update references in all code files (once after all renames)
# Find all text files (source code, Makefiles, configure scripts, etc.) and update references.
echo "Updating references in all relevant files"

find . -type f \( -name "*.c" -o -name "*.h" -o -name "Makefile*" -o -name "*.in" -o -name "*.am" -o -name "*.sh" \) | while read -r referencing_file; do
  for old_file in "${!rename_map[@]}"; do
    new_file=${rename_map[$old_file]}
    echo "Updating reference from $old_file to $new_file in $referencing_file"
    sed -i "s|$old_file|$new_file|g" "$referencing_file"
  done
done

# Restore IFS
IFS=$SAVEIFS

echo "Renaming and reference updates complete."
```



