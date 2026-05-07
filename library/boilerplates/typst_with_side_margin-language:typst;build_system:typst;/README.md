# |||title|||

This template uses a wide right margin for side notes and marginal content.

## Build

```sh
make
```

The template includes local fonts under `fonts/` and imports `template.typ` from
`main.typ`.

## Side Notes

Use the `sidenote` helper from `template.typ` for margin notes:

```typst
#sidenote[Additional context in the margin.]
```
