#!/bin/bash

cp TLPlaylistCreator Package/usr/bin/
dpkg -b Package/ tl-playlist-creator.deb
