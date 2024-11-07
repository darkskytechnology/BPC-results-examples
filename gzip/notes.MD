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

I've opened an issue for this. However, for now, I am just going to use a simple work-around using a script to rename these files (there are hundreds) and fix up all their references (there are thousands).

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
That led to tons of broken links once the files were renamed.

```
#!/bin/bash

# Ensure you run this in the root of your project
# Find all broken symbolic links recursively
broken_links=$(find . -type l ! -exec test -e {} \; -print)

# Iterate over each broken link
for link in $broken_links; do
  # Get the target of the broken symlink
  target=$(readlink "$link")

  # Rename the symlink itself (replace dashes with underscores in the symlink name)
  new_link=$(echo "$link" | sed 's/-/_/g')

  # Check if the target contains dashes
  if [[ "$target" == *"-"* ]]; then
    # Construct a new target by replacing dashes with underscores
    new_target=$(echo "$target" | sed 's/-/_/g')

    # If the new target exists, recreate the symlink with the updated target
    if [ -e "$new_target" ]; then
      echo "Fixing broken link $link -> $target"
      echo "New target: $new_target"
      echo "Renaming symlink: $link -> $new_link"

      # Remove the old broken link
      rm "$link"

      # Create a new symlink with the updated name and target
      ln -s "$new_target" "$new_link"
      echo "Link renamed and fixed: $new_link -> $new_target"
    else
      echo "Warning: Target $new_target does not exist for link $link"
    fi
  else
    echo "Skipping link $link as its target does not contain dashes."
  fi
done

echo "Broken symlink repair and renaming complete."
```

Next, we encounter confusion over the directory named lib and the crate lib produced by Bulletproof Code.

```
2024-10-17T02:13:40.727201Z  INFO main bpc_translate: error[E0761]: file for module `lib` found at both "src/lib.rs" and "src/lib/mod.rs"
  --> src/lib.rs:17:1
   |
17 | pub mod lib;
   | ^^^^^^^^^^^^
   |
   = help: delete or rename one of them to remove the ambiguity


2024-10-17T02:13:40.727237Z  INFO main bpc_translate: warning: found module declaration for lib.rs
  --> src/lib.rs:17:1
   |
17 | pub mod lib;
   | ^^^^^^^^^^^^
   |
   = note: lib.rs is the root of this crate's library target
   = help: to refer to it from other targets, use the library's name as the path
   = note: `#[warn(special_module_name)]` on by default


2024-10-17T02:13:40.727254Z  INFO main bpc_translate: error: aborting due to 1 previous error; 1 warning emitted


2024-10-17T02:13:40.727264Z  INFO main bpc_translate: For more information about this error, try `rustc --explain E0761`.

2024-10-17T02:13:40.727270Z  INFO main bpc_translate: failed to build crate gzip at /home/ubuntu/translations/gzip
2024-10-17T02:13:40.783673Z  INFO main bpc_translate: Initializing a new git repository in `/home/ubuntu/translations/gzip`
2024-10-17T02:13:40.788073Z  INFO main bpc_translate: Setting local git user name and email in `/home/ubuntu/translations/gzip`
2024-10-17T02:13:40.791516Z  INFO main bpc_translate: Adding all files to git repository in `/home/ubuntu/translations/gzip`
2024-10-17T02:13:40.797820Z  INFO main bpc_translate: Creating initial commit in git repository in `/home/ubuntu/translations/gzip`
2024-10-17T02:13:40.808059Z  INFO main bpc_translate: Tagging initial commit with 'Initial first pass translation results' in `/home/ubuntu/translations/gzip`
2024-10-17T02:13:40.809603Z  INFO main bpc_translate: Refactoring gzip using model OpenAI
2024-10-17T02:13:40.851321Z  INFO main bpc_translate: Refactoring Attempt 1 to gather errors and refactor functions
2024-10-17T02:13:41.006583Z  INFO main bpc_translate: Error message: error[E0761]: file for module `lib` found at both "src/lib.rs" and "src/lib/mod.rs"
  --> src/lib.rs:17:1
   |
17 | pub mod lib;
   | ^^^^^^^^^^^^
   |
   = help: delete or rename one of them to remove the ambiguity


2024-10-17T02:13:41.006616Z  INFO main bpc_translate: Processing file: src/lib.rs, line number: 17
2024-10-17T02:13:41.006623Z  INFO main bpc_translate: Mapping function ranges for file: /home/ubuntu/translations/gzip/src/lib.rs
2024-10-17T02:13:41.006642Z  INFO main bpc_translate: Mapping function ranges in file: /home/ubuntu/translations/gzip/src/lib.rs
2024-10-17T02:13:41.007107Z  WARN main bpc_translate: No functions detected in file: /home/ubuntu/translations/gzip/src/lib.rs
2024-10-17T02:13:41.007132Z  INFO main bpc_translate: Function ranges mapped for file: /home/ubuntu/translations/gzip/src/lib.rs
2024-10-17T02:13:41.007139Z  WARN main bpc_translate: No matching function found for error at line 17
2024-10-17T02:13:41.007167Z  INFO main bpc_translate: Error message: warning: found module declaration for lib.rs
  --> src/lib.rs:17:1
   |
17 | pub mod lib;
   | ^^^^^^^^^^^^
   |
   = note: lib.rs is the root of this crate's library target
   = help: to refer to it from other targets, use the library's name as the path
   = note: `#[warn(special_module_name)]` on by default


2024-10-17T02:13:41.007182Z  INFO main bpc_translate: Processing file: src/lib.rs, line number: 17
2024-10-17T02:13:41.007210Z  WARN main bpc_translate: No matching function found for error at line 17
2024-10-17T02:13:41.007232Z  INFO main bpc_translate: Error message: error: aborting due to 1 previous error; 1 warning emitted
```

After manually rename those to `rename_lib`: `sed -i 's/lib/rename_lib/g' gzip.toml` we succeed for a bit until we encounter the use of `static` function declarations, but we have not built into any of our system yet.

