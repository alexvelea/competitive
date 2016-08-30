alias g++="/usr/local/Cellar/gcc/5.3.0/bin/g++-5"
alias vgrind="valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all"
alias 5="md5"
alias shitSlow="pkill -15 -u velea"
alias vim='mvim -v'
alias ll="ls -A -l"
alias csap="cd ~/work/CSAProblems/"

alias size="ls -lR | awk '{s+=$5} END {print s}'"

sudo() {
    echo "The Doors of Durin, Lord of Moria. Speak, friend, and enter."
    command sudo "$@"
}

alias python="python3"
alias work="cd ~/work/"

alias subl="open -a /Applications/Sublime\ Text.app/"
 
alias csa="cd ~/work/CSAcademy/csacademy/"
alias code="cd ~/work/CSacademy/csacademy/content/static/ranking_system/code_refactored/"
alias runserver="autossh -f -M 0 -N -L 15432:localhost:5432 root@linode-dev; autossh -f -M 0 -N -L 16379:localhost:6379 root@linode-dev; python manage.py runserver"

export HISTCONTROL=ignoredups:erasedups  # no duplicate entries
export HISTSIZE=100000                   # big big history
export HISTFILESIZE=100000               # big big history
shopt -s histappend                      # append to history, don't overwrite it

# Save and reload the history after each command finishes
# export PROMPT_COMMAND="history -a; history -c; history -r; $PROMPT_COMMAND"

viewmd() {
    pandoc $1 | lynx -stdin    
}

comp() {
    clang++ -std=c++14 -O2 -Wall $1 -o _${1%%.*} -lm 
}

exec() {
    clang++ -std=c++14 -O2 -Wall $1 -o _${1%%.*} -lm 
    time ./_${1%%.*}
    rm _${1%%.*}
}

# MacPorts Installer addition on 2015-11-16_at_20:07:53: adding an appropriate PATH variable for use with MacPorts.
export PATH="/opt/local/bin:/opt/local/sbin:$PATH"
# Finished adapting your PATH environment variable for use with MacPorts.
 
