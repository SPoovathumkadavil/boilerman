# boilerman

`boilerman` creates new projects from local boilerplate directories.

## Build

```sh
make build
```

Run the test suite:

```sh
make test
```

Install the executable and bundled boilerplates:

```sh
make install
```

## Boilerplate Location

By default, `boilerman` reads boilerplates from:

```text
$HOME/.local/library/boilerman/boilerplates
```

Set `BOILERMAN_LIBRARY_DIR` to use another library root. `boilerman` will look
for a `boilerplates` directory inside that root.

## Boilerplate Format

Each boilerplate is a directory. The directory name starts with the displayed
template name, followed by metadata tags:

```text
cpp_app-language:cpp;build_system:Makefile;
```

Template variables use triple pipes:

```text
|||name|||
```

Variables are resolved in file paths and file contents. Files or directories
whose names start with `~` are copied directly with the leading `~` removed, so
their contents are not template-resolved.
