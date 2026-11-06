# Hoenn walking expedition candidate

Local firmware: `1.36.2-hoenn-walk-local`. Public installer: `1.36.2` (same features as a debug-free release build).
The debug build stays local; the public release is published only on request.

## Walking bonus

Choose a site and a duration. Targets are 250 / 500 / 1,000 steps for
15 / 30 / 60 minutes. Only detected steps during the tour count, including
with the display off and across midnight. No walking is required for the
normal item or the site seal.

The additional item is energy at the coast, care in the forest and training
at the volcano. Coast/forest bonuses have a 10 / 15 / 20 percent training
upgrade chance, fixed at departure. A full bonus slot or maxed training gives
10 energy instead. Claiming a tour pays the bonus once.

Save backup version 2 includes walking progress. Public 1.36.1 backups and
the previous local Hoenn backups are accepted; existing tours keep their
main reward without a retrospective walking bonus.

## Local hardware acceptance (reported done)

The owner reported on 2026-11-06 that this build has been running on hardware
for several weeks. The checklist below is kept as the reference procedure.

Run `bash tools/build_web_local.sh`, serve `web` on localhost and flash using
`/dev.html`. Leave Erase device unchecked. Sprites do not need reinstalling.

- Check site names, goals and earned-bonus text in all six languages.
- Start a tour, walk with display on/off and check the progress.
- Reboot during a tour and check that saved progress remains.
- Claim a normal item and a walking bonus, then verify no second claim.
- Check full bonus inventory and maxed training give energy instead.
- Check backup/restore preserves the active tour and earned bonus.

These physical tests cannot be replaced by the native test suite.
