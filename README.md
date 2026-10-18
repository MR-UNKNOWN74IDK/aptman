# aptman

An English port of [Limou233's aptman](https://github.com/Limou233/aptman) — a small CLI tool that converts `apt` commands into their `pacman` equivalents, for Debian/Ubuntu users learning Arch Linux.

Forked and translated to English while dual-booting Arch alongside Windows, as a way to use familiar `apt` syntax without having to memorise `pacman` commands from scratch. This port later served as the inspiration credited in [aptarch](https://github.com/MR-UNKNOWN74IDK/aptarch), a more complete Rust rewrite.

---

## What it does

Takes `apt` commands and converts them into the correct `pacman` equivalents and runs them. Includes a handful of easter eggs borrowed from the original `apt moo`.

---

## Build from source

```bash
# Clone the repository
git clone https://github.com/MR-UNKNOWN74IDK/aptman.git
cd aptman

# Make the build script executable
chmod +x build.sh

# Build
./build.sh

# Run
./build/aptman
```

> If you use CLion, you can open the project and run it directly.

---

## Status

Not deprecated or archived — just not under independent active development. Updates to this port follow whatever happens upstream in the original project: if it gets updated, this gets updated accordingly.

My actively maintained flagship project is [aptOS](https://github.com/MR-UNKNOWN74IDK/aptOS).

---

## Credits

Original project by [Limou233](https://github.com/Limou233/aptman). This is an English port with minor modifications.

---

## License

MIT — see [LICENSE](./LICENSE) for details.
