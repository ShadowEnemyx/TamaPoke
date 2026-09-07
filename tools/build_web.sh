#!/bin/bash
# Current public installer: the debug-free Gen-3 release.
exec bash "$(dirname "$0")/build_web_gen3.sh" "$@"
