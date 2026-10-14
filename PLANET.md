# Planet macOS compatibility branch

This branch preserves the Wine changes used to run the original Unity 5.3 Planet executable on macOS with Rosetta and DXMT.

## Base and companion code

- Upstream is https://github.com/wine-mirror/wine.
- Base is `wine-11.16`, commit `8da89f8493b21ebfbe344a54dbef0cde23c7ea59`.
- Companion DXMT code is https://github.com/fireyang/dxmt/tree/planet-macos, based on `v0.60`.

## Changes and source attribution

The `wow64cpu` change ports CodeWeavers CW HACK 20760 from the publicly released CrossOver 26.3.0 source archive at https://media.codeweavers.com/pub/crossover/source/crossover-sources-26.3.0.tar.gz. It detects Rosetta and uses far calls and returns for the 32-bit to 64-bit transition. The upstream source copyright notices and LGPL terms remain in place.

The Mac driver exports a versioned native Metal surface API in `include/wine/macdrv_metal.h`. The API keeps native pointers on the host side and manages client-surface attachment, presentation, and release. The companion DXMT branch consumes this API.

Wine retains its upstream license files and per-file notices. See `LICENSE` and `COPYING.LIB`.

## Validation recorded before archival

The local project recorded successful Wine and DXMT builds and observation of the original D3D11 game scene. Full interaction checks, long runs, and reproduction in a clean environment remain incomplete. Archival checks confirm that all nine changed source files match the saved project patches exactly. Archiving does not add a new runtime acceptance result.
