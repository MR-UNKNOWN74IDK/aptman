# apt ↔ pacman Command Comparison Table
| Category | apt Command | pacman Equivalent | Notes |
|------|---------|-----------|------|
| 1-Direct mapping | apt update | pacman -Sy | Sync the package database |
| 1-Direct mapping | apt upgrade | pacman -Su | Upgrade installed packages |
| 1-Direct mapping | apt full-upgrade | pacman -Syu | Sync the database and upgrade (handles dependency changes) |
| 1-Direct mapping | apt install <pkg> | pacman -S <pkg> | Install a package |
| 1-Direct mapping | apt reinstall <pkg> | pacman -S <pkg> | Reinstall (pacman overwrites by default; `--needed` prevents it) |
| 1-Direct mapping | apt remove <pkg> | pacman -R <pkg> | Remove a package (keeps configuration) |
| 1-Direct mapping | apt purge <pkg> | pacman -Rns <pkg> | Remove the package, its configuration, and unused dependencies |
| 1-Direct mapping | apt search <keyword> | pacman -Ss <keyword> | Search repository packages |
| 1-Direct mapping | apt show <pkg> | pacman -Si <pkg> | View repository package details |
| 1-Direct mapping | apt download <pkg> | pacman -Sw <pkg> | Download the package to the cache only |
| 1-Direct mapping | apt clean | pacman -Scc | Clear the entire cache |
| 1-Direct mapping | apt autoclean | pacman -Sc | Clean only the cache of uninstalled packages |
| 1-Direct mapping | apt -h / --help | pacman -h / --help | Help information |
| 1-Direct mapping | apt -v / --version | pacman -V / --version | Version information |
| 2-Composed mapping | apt list | pacman -Q / -Sl / -Ss | Split by scenario: -Q installed, -Sl repository list, -Ss search |
| 2-Composed mapping | apt list --installed | pacman -Q | List of installed packages |
| 2-Composed mapping | apt list --upgradeable | pacman -Qu | List of upgradeable packages |
| 2-Composed mapping | apt list -a <pkg> | pacman -Sl \| grep <pkg> | View all available versions in the repository |
| 2-Composed mapping | apt autoremove | pacman -Rns $(pacman -Qdtq) | Remove orphaned packages (no other package depends on them) |
| 2-Composed mapping | apt autopurge | pacman -Rns $(pacman -Qdtq) | Same as autoremove; pacman -n already removes configuration |
| 2-Composed mapping | apt depends <pkg> | pacman -Si <pkg> \| grep 'Depends On' / pactree <pkg> | Dependency tree requires installing pacman-contrib |
| 2-Composed mapping | apt rdepends <pkg> | pacman -Qi <pkg> \| grep 'Required By' / pactree -r <pkg> | Reverse dependencies require pacman-contrib |
| 2-Composed mapping | apt policy <pkg> | pacman -Si <pkg> \| grep -E 'Repository\|Version' / pacman -Sl \| grep <pkg> | Version priority requires a combined query |
| 2-Composed mapping | apt satisfy 'deps...' | pacman -T <pkg1> <pkg2> + pacman -S <pkg1> <pkg2> | -T detects what's missing, -S installs; no single-string parsing feature |
| 2-Composed mapping | apt build-dep <pkg> | asp export <pkg> → parse PKGBUILD makedepends → pacman -S / makepkg -s | Or just use makepkg -s to auto-install build dependencies |
| 2-Composed mapping | apt install -y <pkg> | pacman -S --noconfirm <pkg> | Auto-confirm |
| 2-Composed mapping | apt install -d <pkg> | pacman -Sw <pkg> | Download only |
| 2-Composed mapping | apt install -s <pkg> | pacman -Sp <pkg> | Only prints the download URI (not a full simulation) |
| 2-Composed mapping | apt remove --purge <pkg> | pacman -Rns <pkg> | Complete removal |
| 2-Composed mapping | apt full-upgrade -s --print-uris | pacman -Syu --print | Print download links |
| 2-Composed mapping | apt -c <file> | pacman --config <file> | Specify a configuration file |
| 2-Composed mapping | apt -q / --quiet | pacman -q / --quiet | Quiet output |
| 2-Composed mapping | apt -d / --download-only | pacman -w / --downloadonly | Download only |
| 2-Composed mapping | apt --reinstall | pacman -S (without --needed) | Force reinstallation |
| 2-Composed mapping | apt --no-upgrade | pacman -S --needed | Don't reinstall an already-existing version |
| 2-Composed mapping | apt --print-uris | pacman -Sp | Print URIs |
| 3-No equivalent | apt changelog <pkg> | No equivalent | Arch packages have no built-in changelog mechanism. Alternative: install asp, then run `asp log <pkg>` to view the PKGBUILD commit history; or check the upstream release notes. |
| 3-No equivalent | apt source <pkg> | No equivalent | pacman has no built-in source-download command. Alternative: install the asp tool, then run `asp export <pkg>` (exports the latest PKGBUILD) or `asp checkout <pkg>` (gets the full Git history). You can also download manually from the Arch Linux Archive (ALA). |
| 3-No equivalent | apt edit-sources | No equivalent | pacman has no built-in editor-invocation command. Alternative: manually edit `/etc/pacman.conf` and `/etc/pacman.d/mirrorlist` (e.g. `sudo nano /etc/pacman.conf`). |
| 3-No equivalent | apt moo | No equivalent | pacman has no easter-egg command. No alternative. |
| 3-No equivalent | apt list (status markers) | No equivalent | pacman has no list format with status markers like [installed,automatic] or [upgradable from: x]. `pacman -Q` only outputs the package name and version, with no repository-origin or install-method markers. |
| 3-No equivalent | apt satisfy (complex dependency strings) | No equivalent | pacman has no feature for parsing and installing complex dependency strings like `apt satisfy 'pkg1, pkg2 (>= 1.0)'`. `pacman -T` only detects what's missing and outputs package names, without handling version-constraint strings; `pacman -S` can only install by package name. |
| 3-No equivalent | apt --fix-broken | No equivalent | pacman's dependency handling is atomic — if dependencies aren't satisfied during install/upgrade, it fails and rolls back immediately, so there's no separate mode for fixing broken dependencies. |
| 3-No equivalent | apt --no-install-recommends | No equivalent | pacman has no concept of Recommends/Suggests. In Arch repositories, all `depends` are mandatory dependencies; `optdepends` are just hints and are never installed automatically. |
| 3-No equivalent | apt -t <release> / --target-release | No equivalent | Arch is a rolling release distribution with no concept of release branches. pacman does not support installing by target release. |
| 3-No equivalent | apt -a <arch> / --architecture | No equivalent | pacman handles architecture automatically; there's no separate option for filtering installs by architecture. |
