#!/bin/bash
cd /home/abosc/Documents/Cercle_3/Minishell/mininours
(
echo "<< eof | cat"
echo "salut"
echo "ca"
echo "va"
echo "?"
echo "eof"
) | ./minishell
