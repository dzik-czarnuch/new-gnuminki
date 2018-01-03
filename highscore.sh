#!/bin/bash
FOLDER="$HOME/.local/share/gnuminki"

mkdir -p $FOLDER
touch $FOLDER/highscores
echo "$(whoami) has started a new game at $(date +"%D %H:%M:%S")" >> $FOLDER/highscores

if [ $(grep -c $(whoami) $FOLDER/highscores) -eq 1 ]
    then
        touch $FOLDER/playerList
        echo $(whoami) >> $FOLDER/playerList
fi