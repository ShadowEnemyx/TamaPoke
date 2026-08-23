#!/usr/bin/env python3
"""Empaqueta todos los sprites de la SD (tools/sdcard/mons/*.bin) en un unico
fichero web/sprites.pak para que el instalador web los suba de un clic.

Formato TPAK (little-endian):
  char[4]  "TPAK"
  uint16   count
  count x { uint8 nameLen; char name[nameLen]; uint32 size }   (indice)
  ...datos de cada fichero, en el mismo orden...

El instalador (web/index.html) lo descarga, lo parte por el indice y manda cada
fichero a la placa con el protocolo PUT (igual que tools/send_sd.py).
"""
import glob
import os
import struct
import sys

HERE = os.path.dirname(__file__)
MONS = os.path.join(HERE, 'sdcard', 'mons')
OUT = os.path.join(HERE, '..', 'web', 'sprites.pak')
GEN2_OUT = os.path.join(HERE, '..', 'web', 'sprites-gen2-update.pak')


def main():
    gen2_only = '--gen2' in sys.argv[1:]
    if gen2_only:
        files = [os.path.join(MONS, f'p{n:03d}.bin') for n in range(161, 252)]
        files += [os.path.join(MONS, f'ps{n:03d}.bin') for n in range(161, 252)]
        # thumbs.bin is a complete index and must accompany a partial sprite
        # update so the gallery can address all 251 entries.
        files.append(os.path.join(MONS, 'thumbs.bin'))
        out_path = GEN2_OUT
    else:
        files = sorted(glob.glob(os.path.join(MONS, '*.bin')))
        out_path = OUT
    if not files:
        raise SystemExit('no hay sprites en ' + MONS)
    names = ['mons/' + os.path.basename(f) for f in files]
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
