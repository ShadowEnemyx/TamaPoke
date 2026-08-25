#!/usr/bin/env python3
"""Empaqueta el conjunto estable #1–251 en web/sprites.pak para que el
instalador público lo suba de un clic. Los conjuntos locales Gen-3 se generan
con --gen3 o --gen3-full.

Formato TPAK (little-endian):
  char[4]  "TPAK"
  uint16   count
  count x { uint8 nameLen; char name[nameLen]; uint32 size }   (indice)
  ...datos de cada fichero, en el mismo orden...

El instalador (web/index.html) lo descarga, lo parte por el indice y manda cada
fichero a la placa con el protocolo PUT (igual que tools/send_sd.py).

Flags locales: --gen2 (161–251), --gen3 (252–386) y --gen3-full (1–386).
"""
import os
import struct
import sys

HERE = os.path.dirname(__file__)
MONS = os.path.join(HERE, 'sdcard', 'mons')
OUT = os.path.join(HERE, '..', 'web', 'sprites.pak')
GEN2_OUT = os.path.join(HERE, '..', 'web', 'sprites-gen2-update.pak')
GEN3_OUT = os.path.join(HERE, '..', 'web', 'sprites-gen3-update.pak')
GEN3_FULL_OUT = os.path.join(HERE, '..', 'web', 'sprites-gen3-full.pak')
PUBLIC_THUMBS = os.path.join(MONS, 'thumbs-public.bin')


def main():
    args = sys.argv[1:]
    gen2_only = '--gen2' in args
    gen3_only = '--gen3' in args
    gen3_full = '--gen3-full' in args
    output = None
    if '--output' in args:
        output_index = args.index('--output')
        if output_index + 1 >= len(args):
            raise SystemExit('--output requires a path')
        output = args[output_index + 1]
    if sum((gen2_only, gen3_only, gen3_full)) > 1:
        raise SystemExit('choose one of --gen2, --gen3 or --gen3-full')
    if gen2_only:
        files = [os.path.join(MONS, f'p{n:03d}.bin') for n in range(161, 252)]
        files += [os.path.join(MONS, f'ps{n:03d}.bin') for n in range(161, 252)]
        # thumbs.bin is a complete index and must accompany a partial sprite
        # update so the gallery can address all 251 entries.
        files.append(os.path.join(MONS, 'thumbs.bin'))
        out_path = output or GEN2_OUT
    elif gen3_only:
        files = [os.path.join(MONS, f'p{n:03d}.bin') for n in range(252, 387)]
        files += [os.path.join(MONS, f'ps{n:03d}.bin') for n in range(252, 387)]
        # thumbs.bin is a complete index and must accompany a partial sprite
        # update so the gallery can address all 386 entries.
        files.append(os.path.join(MONS, 'thumbs.bin'))
        out_path = output or GEN3_OUT
    elif gen3_full:
        files = [os.path.join(MONS, f'p{n:03d}.bin') for n in range(1, 387)]
        files += [os.path.join(MONS, f'ps{n:03d}.bin') for n in range(1, 387)]
        files.append(os.path.join(MONS, 'thumbs.bin'))
        out_path = output or GEN3_FULL_OUT
    else:
        # The public installer is intentionally pinned to the stable #1–251
        # set. A local Gen-3 run may have extra files in this directory, so do
        # not use a broad glob here. The public thumbnail index is renamed in
        # the TPAK below to the firmware's expected mons/thumbs.bin path.
        files = [os.path.join(MONS, f'p{n:03d}.bin') for n in range(1, 252)]
        files += [os.path.join(MONS, f'ps{n:03d}.bin') for n in range(1, 252)]
        files.append(PUBLIC_THUMBS)
        out_path = output or OUT
    if not files:
        raise SystemExit('no hay sprites en ' + MONS)
    names = ['mons/thumbs.bin' if f == PUBLIC_THUMBS else 'mons/' + os.path.basename(f)
             for f in files]
    blobs = [open(f, 'rb').read() for f in files]

    with open(out_path, 'wb') as o:
        o.write(b'TPAK')
        o.write(struct.pack('<H', len(files)))
        for name, blob in zip(names, blobs):
            nb = name.encode()
            o.write(struct.pack('<B', len(nb)))
            o.write(nb)
            o.write(struct.pack('<I', len(blob)))
        for blob in blobs:
            o.write(blob)

    total = sum(len(b) for b in blobs)
    print(f'{os.path.normpath(out_path)}: {len(files)} sprites, {total / 1048576:.1f} MB datos '
          f'({os.path.getsize(out_path) / 1048576:.1f} MB total)')


if __name__ == '__main__':
    main()
