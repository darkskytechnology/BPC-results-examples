# Project source

https://github.com/nasa/cFS

# Translation Attempt (with debugging enabled)

https://bpc-results-examples.s3.amazonaws.com/cFS.mov

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

The directory `i686-linux-gnu` needed to be manually renamed to `i686_linux_gnu`. After that, we fail to process this declaration (likely because of the terminating entry?)

```
CFE_ConfigTool_DetailEntry_t MAP_ENTRY_LIST[] = {
    {
        .render_style = CFE_ConfigTool_RenderStyle_ARRAY,
        .ido          = CFE_ConfigIdOffset_PLATFORM_TBL_VALID_SCID,
        .u.list =
            {
                .prefix      = "CFE_PLATFORM_TBL_VALID_SCID",
                .type_name   = "uint32_t",
                .num_entries = CFE_PLATFORM_TBL_VALID_SCID_COUNT,
            },
    },
    {
        .render_style = CFE_ConfigTool_RenderStyle_ARRAY,
        .ido          = CFE_ConfigIdOffset_PLATFORM_TBL_VALID_PRID,
        .u.list =
            {
                .prefix      = "CFE_PLATFORM_TBL_VALID_PRID",
                .type_name   = "uint32_t",
                .num_entries = CFE_PLATFORM_TBL_VALID_PRID_COUNT,
            },
    },
    {
        .render_style = CFE_ConfigTool_RenderStyle_ARRAY,
        .ido          = CFE_ConfigIdOffset_PLATFORM_ES_MEM_BLOCK_SIZE,
        .u.list       = {.prefix      = "CFE_PLATFORM_ES_MEM_BLOCK_SIZE",
                   .type_name   = "size_t",
                   .num_entries = CFE_PLATFORM_ES_POOL_MAX_BUCKETS,
                   .custom_max  = "CFE_PLATFORM_ES_MAX_BLOCK_SIZE",
                   .options     = CFE_CONFIGTOOL_LIST_DESCENDING | CFE_CONFIGTOOL_USE_LEADING_ZERO},
    },
    {
        .render_style = CFE_ConfigTool_RenderStyle_ARRAY,
        .ido          = CFE_ConfigIdOffset_PLATFORM_ES_CDS_MEM_BLOCK_SIZE,
        .u.list       = {.prefix      = "CFE_PLATFORM_ES_CDS_MEM_BLOCK_SIZE",
                   .type_name   = "size_t",
                   .num_entries = CFE_PLATFORM_ES_POOL_MAX_BUCKETS,
                   .custom_max  = "CFE_PLATFORM_ES_CDS_MAX_BLOCK_SIZE",
                   .options     = CFE_CONFIGTOOL_LIST_DESCENDING | CFE_CONFIGTOOL_USE_LEADING_ZERO},
    },
    {
        .render_style = CFE_ConfigTool_RenderStyle_ARRAY,
        .ido          = CFE_ConfigIdOffset_PLATFORM_SB_MEM_BLOCK_SIZE,
        .u.list       = {.prefix      = "CFE_PLATFORM_SB_MEM_BLOCK_SIZE",
                   .type_name   = "size_t",
                   .num_entries = CFE_PLATFORM_SB_POOL_MAX_BUCKETS,
                   .custom_max  = "CFE_PLATFORM_SB_MAX_BLOCK_SIZE",
                   .options     = CFE_CONFIGTOOL_LIST_DESCENDING | CFE_CONFIGTOOL_USE_LEADING_ZERO},
    },

    {0} /* Keep this last */
};
```

`/targets/cFS/cfe/modules/config/tool/cfeconfig_platformdata_table.c` is the original source.

We come up with:

```
let map_entry_list = [
    CFE_ConfigTool_DetailEntry_t {
        render_style: CFE_ConfigTool_RenderStyle_ARRAY,
        ido: CFE_ConfigIdOffset_PLATFORM_TBL_VALID_SCID,
        u: CFE_ConfigTool_DetailEntryUnion {
            list: CFE_ConfigTool_ListDetail {
                prefix: "CFE_PLATFORM_TBL_VALID_SCID",
                type_name: "uint32_t",
                num_entries: CFE_PLATFORM_TBL_VALID_SCID_COUNT,
                custom_max: None,
                options: 0,
            },
        },
    },
    CFE_ConfigTool_DetailEntry_t {
        render_style: CFE_ConfigTool_RenderStyle_ARRAY,
        ido: CFE_ConfigIdOffset_PLATFORM_TBL_VALID_PRID,
        u: CFE_ConfigTool_DetailEntryUnion {
            list: CFE_ConfigTool_ListDetail {
                prefix: "CFE_PLATFORM_TBL_VALID_PRID",
                type_name: "uint32_t",
                num_entries: CFE_PLATFORM_TBL_VALID_PRID_COUNT,
                custom_max: None,
                options: 0,
            },
        },
    },
    CFE_ConfigTool_DetailEntry_t {
        render_style: CFE_ConfigTool_RenderStyle_ARRAY,
        ido: CFE_ConfigIdOffset_PLATFORM_ES_MEM_BLOCK_SIZE,
        u: CFE_ConfigTool_DetailEntryUnion {
            list: CFE_ConfigTool_ListDetail {
                prefix: "CFE_PLATFORM_ES_MEM_BLOCK_SIZE",
                type_name: "size_t",
                num_entries: CFE_PLATFORM_ES_POOL_MAX_BUCKETS,
                custom_max: Some("CFE_PLATFORM_ES_MAX_BLOCK_SIZE"),
                options: CFE_CONFIGTOOL_LIST_DESCENDING | CFE_CONFIGTOOL_USE_LEADING_ZERO,
            },
        },
    },
    CFE_ConfigTool_DetailEntry_t {
        render_style: CFE_ConfigTool_RenderStyle_ARRAY,
        ido: CFE_ConfigIdOffset_PLATFORM_ES_CDS_MEM_BLOCK_SIZE,
        u: CFE_ConfigTool_DetailEntryUnion {
            list: CFE_ConfigTool_ListDetail {
                prefix: "CFE_PLATFORM_ES_CDS_MEM_BLOCK_SIZE",
                type_name: "size_t",
                num_entries: CFE_PLATFORM_ES_POOL_MAX_BUCKETS,
                custom_max: Some("CFE_PLATFORM_ES_CDS_MAX_BLOCK_SIZE"),
                options: CFE_CONFIGTOOL_LIST_DESCENDING | CFE_CONFIGTOOL_USE_LEADING_ZERO,
            },
        },
    },
    CFE_ConfigTool_DetailEntry_t {
        render_style: CFE_ConfigTool_RenderStyle_ARRAY,
        ido: CFE_ConfigIdOffset_PLATFORM_SB_MEM_BLOCK_SIZE,
        u: CFE_ConfigTool_DetailEntryUnion {
            list: CFE_ConfigTool_ListDetail {
                prefix: "CFE_PLATFORM_SB_MEM_BLOCK_SIZE",
                type_name: "size_t",
                num_entries: CFE_PLATFORM_SB_POOL_MAX_BUCKETS,
                custom_max: Some("CFE_PLATFORM_SB_MAX_BLOCK_SIZE"),
                options: CFE_CONFIGTOOL_LIST_DESCENDING | CFE_CONFIGTOOL_USE_LEADING_ZERO,
            },
        },
    },
    CFE_ConfigTool_DetailEntry_t { render_style: 0, ido: 0, u: CFE_ConfigTool_DetailEntryUnion { list: CFE_ConfigTool_ListDetail { prefix: "", type_name: "", num_entries:
 0, custom_max: None, options: 0 } } },
]; 
```

After performing manual renaming translation continued following renaming but stopped after failing to process global declaration of MAP_ENTRY_LIST. Later failure due to extensive use of global variables.

```
error: expected item, found keyword `let`
  --> /home/ubuntu/translations/cFS_reduced/src/cfe/modules/config/tool/cfeconfig_platformdata_table_c.rs:75:1
   |
75 | let map_entry_list = [
   | ^^^ consider using `const` or `static` instead of `let` for global variables
```



