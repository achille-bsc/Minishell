#!/bin/bash
# minishell_tester.sh
# Testeur complet, design, avec stats et trace détaillée

MINISHELL=./minishell
REFSHELL=/bin/bash
TRACE=trace.txt
TMPDIR=$(mktemp -d)

# Couleurs et emojis
GREEN='\033[1;32m'
RED='\033[1;31m'
YELLOW='\033[1;33m'
BLUE='\033[1;34m'
CYAN='\033[1;36m'
MAGENTA='\033[1;35m'
RESET='\033[0m'
BOLD='\033[1m'
OK_EMOJI="✅"
KO_EMOJI="❌"
SEP="${MAGENTA}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${RESET}"

# Compteurs
OK_COUNT=0
KO_COUNT=0
TOTAL_COUNT=0
declare -A OK_BY_CAT
declare -A KO_BY_CAT

echo -e "${BOLD}${CYAN}===== TRACE DES TESTS MINISHELL =====${RESET}\n" > "$TRACE"

trap 'rm -rf "$TMPDIR"' EXIT

# Affichage séparateur
print_sep() {
    echo -e "$SEP"
    echo -e "$SEP" >> "$TRACE"
}

# Affichage titre catégorie
print_title() {
    print_sep
    echo -e "${BOLD}${BLUE}\n$1${RESET}"
    echo -e "\n$SEP\n$1\n$SEP" >> "$TRACE"
}

# Affichage sous-titre
print_subtitle() {
    echo -e "${BOLD}${CYAN}$1${RESET}"
    echo -e "$1" >> "$TRACE"
}

# Affichage commande
print_cmd() {
    echo -e "${YELLOW}$ $1${RESET}"
    echo -e "\n$ $1" >> "$TRACE"
}

# Normalisation sortie
normalize_output() {
    sed 's/[[:space:]]*$//' | sed '/^$/N;/^\n$/D'
}

# Test unitaire
run_test() {
    local cat="$1"
    local label="$2"
    local cmd="$3"
    print_cmd "$cmd"
    local minifile="$TMPDIR/minishell.out"
    local bashfile="$TMPDIR/bash.out"
    echo -e "$cmd" | $MINISHELL 2>&1 | tail -n +2 | sed '/Mininours>.*/d' | normalize_output > "$minifile"
    echo -e "$cmd" | $REFSHELL 2>&1 | normalize_output > "$bashfile"
    if diff -q "$minifile" "$bashfile" > /dev/null; then
        echo -e "${GREEN}${OK_EMOJI} $label${RESET}"
        echo -e "${OK_EMOJI} $label : OK" >> "$TRACE"
        OK_COUNT=$((OK_COUNT+1))
        OK_BY_CAT["$cat"]=$(( ${OK_BY_CAT["$cat"]} + 1 ))
    else
        echo -e "${RED}${KO_EMOJI} $label${RESET}"
        echo -e "${KO_EMOJI} $label : KO" >> "$TRACE"
        echo -e "${CYAN}Minishell:${RESET}\n|$(cat "$minifile")|" >> "$TRACE"
        echo -e "${CYAN}Bash     :${RESET}\n|$(cat "$bashfile")|" >> "$TRACE"
        KO_COUNT=$((KO_COUNT+1))
        KO_BY_CAT["$cat"]=$(( ${KO_BY_CAT["$cat"]} + 1 ))
    fi
    TOTAL_COUNT=$((TOTAL_COUNT+1))
}

# ================== DÉFINITION DES TESTS ==================
run_all_tests() {
    # Commandes simples (difficulté croissante)
    print_title "COMMANDES SIMPLES"
    run_test "COMMANDES SIMPLES" "echo vide" "echo"
    run_test "COMMANDES SIMPLES" "echo simple" "echo Hello"
    run_test "COMMANDES SIMPLES" "echo multi args" "echo Hello World Test"
    run_test "COMMANDES SIMPLES" "echo avec espaces" "echo    Hello    World   "
    run_test "COMMANDES SIMPLES" "echo avec tab" "echo 'Hello	World'"
    run_test "COMMANDES SIMPLES" "ls simple" "ls"
    run_test "COMMANDES SIMPLES" "ls avec options" "ls -l"
    run_test "COMMANDES SIMPLES" "ls dossier" "ls /tmp"
    run_test "COMMANDES SIMPLES" "pwd" "pwd"
    run_test "COMMANDES SIMPLES" "whoami" "whoami"
    run_test "COMMANDES SIMPLES" "date" "date"
    run_test "COMMANDES SIMPLES" "cat fichier simple" "cat /etc/hostname"
    run_test "COMMANDES SIMPLES" "wc simple" "echo test | wc"
    run_test "COMMANDES SIMPLES" "grep simple" "echo test | grep test"
    run_test "COMMANDES SIMPLES" "commande inexistante" "commandeinexistante"
    run_test "COMMANDES SIMPLES" "path incorrect" "/inexistant/cmd"

    # Variables d'environnement (difficulté croissante)
    print_title "VARIABLES D'ENVIRONNEMENT"
    run_test "VARIABLES D'ENVIRONNEMENT" "variable PATH" "echo \$PATH"
    run_test "VARIABLES D'ENVIRONNEMENT" "variable HOME" "echo \$HOME"
    run_test "VARIABLES D'ENVIRONNEMENT" "variable inexistante" "echo \$INEXISTANTE"
    run_test "VARIABLES D'ENVIRONNEMENT" "export simple" "export TESTVAR=42; echo \$TESTVAR"
    run_test "VARIABLES D'ENVIRONNEMENT" "export avec espaces" "export TESTVAR='hello world'; echo \$TESTVAR"
    run_test "VARIABLES D'ENVIRONNEMENT" "export vide" "export TESTVAR=; echo \$TESTVAR"
    run_test "VARIABLES D'ENVIRONNEMENT" "export sans valeur" "export TESTVAR; echo \$TESTVAR"
    run_test "VARIABLES D'ENVIRONNEMENT" "export plusieurs" "export A=1 B=2; echo \$A \$B"
    run_test "VARIABLES D'ENVIRONNEMENT" "export overwrite" "export X=1; export X=2; echo \$X"
    run_test "VARIABLES D'ENVIRONNEMENT" "export expansion" "export X=hello; export Y=\$X; echo \$Y"
    run_test "VARIABLES D'ENVIRONNEMENT" "unset simple" "export TESTVAR=test; unset TESTVAR; echo \$TESTVAR"
    run_test "VARIABLES D'ENVIRONNEMENT" "unset inexistante" "unset INEXISTANTE; echo done"
    run_test "VARIABLES D'ENVIRONNEMENT" "unset PATH danger" "unset PATH; echo \$PATH"
    run_test "VARIABLES D'ENVIRONNEMENT" "variable dans commande" "export CMD=echo; \$CMD hello"

    # Redirections (difficulté croissante)
    print_title "REDIRECTIONS"
    run_test "REDIRECTIONS" "> simple" "echo test > $TMPDIR/f1; cat $TMPDIR/f1; rm $TMPDIR/f1"
    run_test "REDIRECTIONS" "> écrasement" "echo test1 > $TMPDIR/f2; echo test2 > $TMPDIR/f2; cat $TMPDIR/f2; rm $TMPDIR/f2"
    run_test "REDIRECTIONS" ">> append" "echo line1 > $TMPDIR/f3; echo line2 >> $TMPDIR/f3; cat $TMPDIR/f3; rm $TMPDIR/f3"
    run_test "REDIRECTIONS" ">> sur fichier inexistant" "echo test >> $TMPDIR/f4; cat $TMPDIR/f4; rm $TMPDIR/f4"
    run_test "REDIRECTIONS" "< simple" "echo test > $TMPDIR/f5; cat < $TMPDIR/f5; rm $TMPDIR/f5"
    run_test "REDIRECTIONS" "< fichier inexistant" "cat < $TMPDIR/inexistant"
    run_test "REDIRECTIONS" "< et > combinés" "echo test > $TMPDIR/f6; cat < $TMPDIR/f6 > $TMPDIR/f7; cat $TMPDIR/f7; rm $TMPDIR/f6 $TMPDIR/f7"
    run_test "REDIRECTIONS" "multiple >" "echo test > $TMPDIR/f8 > $TMPDIR/f9; cat $TMPDIR/f9; rm $TMPDIR/f8 $TMPDIR/f9"
    run_test "REDIRECTIONS" "redirection avec pipe" "echo hello | cat > $TMPDIR/f10; cat $TMPDIR/f10; rm $TMPDIR/f10"
    run_test "REDIRECTIONS" "redirection complexe" "echo test | cat > $TMPDIR/f11; cat < $TMPDIR/f11 | wc > $TMPDIR/f12; cat $TMPDIR/f12; rm $TMPDIR/f11 $TMPDIR/f12"

    # Pipes (difficulté croissante)
    print_title "PIPES"
    run_test "PIPES" "pipe simple" "echo hello | cat"
    run_test "PIPES" "pipe avec wc" "echo hello world | wc -w"
    run_test "PIPES" "pipe avec grep" "echo hello | grep hello"
    run_test "PIPES" "pipe double" "echo hello | cat | cat"
    run_test "PIPES" "pipe triple" "echo hello | cat | cat | cat"
    run_test "PIPES" "pipe long" "echo hello | cat | cat | cat | cat | cat"
    run_test "PIPES" "ls pipe wc" "ls | wc -l"
    run_test "PIPES" "pipe avec sort" "echo -e 'c\nb\na' | sort"
    run_test "PIPES" "pipe avec head" "echo -e 'line1\nline2\nline3' | head -2"
    run_test "PIPES" "pipe complexe" "echo hello world | grep world | wc -c"
    run_test "PIPES" "pipe avec variables" "export MSG=hello; echo \$MSG | cat"
    run_test "PIPES" "pipe vide" "echo | cat"

    # Builtins (difficulté croissante)
    print_title "BUILTINS"
    run_test "BUILTINS" "pwd simple" "pwd"
    run_test "BUILTINS" "env simple" "env"
    run_test "BUILTINS" "env grep" "env | grep PATH"
    run_test "BUILTINS" "echo builtin" "echo hello"
    run_test "BUILTINS" "echo -n simple" "echo -n hello"
    run_test "BUILTINS" "echo -n vide" "echo -n"
    run_test "BUILTINS" "export affichage" "export"
    run_test "BUILTINS" "export simple" "export TEST=value; echo \$TEST"
    run_test "BUILTINS" "export multiple" "export A=1 B=2 C=3; echo \$A\$B\$C"
    run_test "BUILTINS" "unset simple" "export TEST=value; unset TEST; echo \$TEST"
    run_test "BUILTINS" "cd home" "cd ~; pwd"
    run_test "BUILTINS" "cd tmp" "cd /tmp; pwd"
    run_test "BUILTINS" "cd -" "cd /tmp; cd ~; cd -; pwd"
    run_test "BUILTINS" "cd inexistant" "cd /dossier/inexistant"
    run_test "BUILTINS" "cd sans permission" "cd /root"
    run_test "BUILTINS" "exit simple" "exit"
    run_test "BUILTINS" "exit avec code" "exit 42"

    # Quotes et échappement (difficulté croissante)
    print_title "QUOTES ET ÉCHAPPEMENT"
    run_test "QUOTES ET ÉCHAPPEMENT" "simple quotes" "echo 'hello world'"
    run_test "QUOTES ET ÉCHAPPEMENT" "double quotes" "echo \"hello world\""
    run_test "QUOTES ET ÉCHAPPEMENT" "quotes vides" "echo ''"
    run_test "QUOTES ET ÉCHAPPEMENT" "double quotes vides" "echo \"\""
    run_test "QUOTES ET ÉCHAPPEMENT" "quotes avec variables" "export X=test; echo \"hello \$X\""
    run_test "QUOTES ET ÉCHAPPEMENT" "simple quotes avec variables" "export X=test; echo 'hello \$X'"
    run_test "QUOTES ET ÉCHAPPEMENT" "quotes imbriquées" "echo \"hello 'world'\""
    run_test "QUOTES ET ÉCHAPPEMENT" "échappement simple" "echo hello\\ world"
    run_test "QUOTES ET ÉCHAPPEMENT" "échappement quotes" "echo \"hello \\\"world\\\"\""
    run_test "QUOTES ET ÉCHAPPEMENT" "quotes multiples" "echo 'hello' \"world\" test"

    # Erreurs (difficulté croissante)
    print_title "ERREURS"
    run_test "ERREURS" "commande inexistante" "commandeinexistante"
    run_test "ERREURS" "fichier inexistant" "cat fichier_inexistant"
    run_test "ERREURS" "permission denied" "cat /etc/shadow"
    run_test "ERREURS" "pipe syntax error" "ls | | wc"
    run_test "ERREURS" "pipe en début" "| ls"
    run_test "ERREURS" "pipe en fin" "ls |"
    run_test "ERREURS" "redirection syntax" "ls >"
    run_test "ERREURS" "redirection sans fichier" "echo test >"
    run_test "ERREURS" "quote non fermée simple" "echo 'hello"
    run_test "ERREURS" "quote non fermée double" "echo \"hello"
    run_test "ERREURS" "export invalid" "export 123=value"
    run_test "ERREURS" "export avec =" "export =value"
    run_test "ERREURS" "unset sans args" "unset"
    run_test "ERREURS" "cd trop d'args" "cd /tmp /home"

    # Tests spéciaux et edge cases
    print_title "TESTS SPÉCIAUX"
    run_test "TESTS SPÉCIAUX" "commande vide" ""
    run_test "TESTS SPÉCIAUX" "espaces seulement" "   "
    run_test "TESTS SPÉCIAUX" "tabs seulement" "		"
    run_test "TESTS SPÉCIAUX" "newlines" "echo -e 'line1\nline2'"
    run_test "TESTS SPÉCIAUX" "caractères spéciaux" "echo '!@#\$%^&*()'"
    run_test "TESTS SPÉCIAUX" "très long argument" "echo $(printf 'a%.0s' {1..1000})"
    run_test "TESTS SPÉCIAUX" "beaucoup d'espaces" "echo          hello          world"
    run_test "TESTS SPÉCIAUX" "variable recursive" "export X=\$X; echo \$X"
    run_test "TESTS SPÉCIAUX" "PATH vide" "export PATH=; ls"
    run_test "TESTS SPÉCIAUX" "HOME inexistant" "export HOME=/inexistant; cd"

    # =================== BONUS ===================
    print_title "✨✨✨ BONUS ✨✨✨"

    # Opérateurs logiques && et || (difficulté croissante)
    print_subtitle "Opérateurs logiques &&, ||"
    run_test "BONUS: Priorités" "true simple" "true && echo OK"
    run_test "BONUS: Priorités" "false simple" "false && echo KO"
    run_test "BONUS: Priorités" "or true" "false || echo OK"
    run_test "BONUS: Priorités" "or false" "true || echo KO"
    run_test "BONUS: Priorités" "and-or simple" "true && false || echo OK"
    run_test "BONUS: Priorités" "or-and simple" "false || true && echo OK"
    run_test "BONUS: Priorités" "chaîne and" "true && true && echo OK"
    run_test "BONUS: Priorités" "chaîne or" "false || false || echo OK"
    run_test "BONUS: Priorités" "exit codes" "ls /tmp && echo 'ls ok' || echo 'ls failed'"
    run_test "BONUS: Priorités" "commandes complexes" "echo A && echo B || echo C"
    run_test "BONUS: Priorités" "avec variables" "export X=true; \$X && echo OK"
    run_test "BONUS: Priorités" "avec pipes" "echo hello | grep hello && echo found"
    run_test "BONUS: Priorités" "avec redirections" "echo test > $TMPDIR/f && cat $TMPDIR/f && rm $TMPDIR/f"
    run_test "BONUS: Priorités" "très long" "true && true && true && true && echo OK"

    # Parenthèses et groupements (difficulté croissante)
    print_subtitle "Parenthèses et groupements"
    run_test "BONUS: Priorités" "parenthèses simples" "(echo hello)"
    run_test "BONUS: Priorités" "parenthèses avec and" "(true && echo OK)"
    run_test "BONUS: Priorités" "parenthèses avec or" "(false || echo OK)"
    run_test "BONUS: Priorités" "groupement priorité" "(true && false) || echo OK"
    run_test "BONUS: Priorités" "groupement complexe" "(false && echo KO) || (true && echo OK)"
    run_test "BONUS: Priorités" "groupement avec pipes" "(echo hello | cat) && echo done"
    run_test "BONUS: Priorités" "parenthèses imbriquées" "((true && echo inner) && echo outer)"
    run_test "BONUS: Priorités" "groupement variables" "(export X=test; echo \$X) && echo done"
    run_test "BONUS: Priorités" "parenthèses multiples" "(echo A && echo B) || (echo C && echo D)"
    run_test "BONUS: Priorités" "priorité complexe" "true && (false || echo OK) && echo final"

    # Wildcards * (difficulté croissante)
    print_subtitle "Wildcards *"
    run_test "BONUS: Wildcards" "star simple" "echo *"
    run_test "BONUS: Wildcards" "star dans dossier" "echo /tmp/*"
    run_test "BONUS: Wildcards" "star avec extension" "echo *.c"
    run_test "BONUS: Wildcards" "star en début" "echo *rc"
    run_test "BONUS: Wildcards" "star en fin" "echo Make*"
    run_test "BONUS: Wildcards" "star au milieu" "echo M*e"
    run_test "BONUS: Wildcards" "double star" "echo *.*"
    run_test "BONUS: Wildcards" "star avec path" "echo src/*.c"
    run_test "BONUS: Wildcards" "star inexistant" "echo *.zzz"
    run_test "BONUS: Wildcards" "multiple stars" "echo *.* *.*"
    run_test "BONUS: Wildcards" "star avec commandes" "ls *.c"
    run_test "BONUS: Wildcards" "star avec pipes" "echo *.h | wc -w"
    run_test "BONUS: Wildcards" "star avec redirections" "ls *.c > $TMPDIR/f; cat $TMPDIR/f; rm $TMPDIR/f"
    run_test "BONUS: Wildcards" "star complexe" "echo */*"

    # Tests bonus combinés (très difficiles)
    print_subtitle "Combinaisons bonus"
    run_test "BONUS: Combiné" "wildcard + and" "ls *.c && echo found"
    run_test "BONUS: Combiné" "wildcard + or" "ls *.zzz || echo not_found"
    run_test "BONUS: Combiné" "wildcard + parenthèses" "(ls *.c) && echo OK"
    run_test "BONUS: Combiné" "and + wildcard + pipe" "ls *.h && echo *.c | wc -w"
    run_test "BONUS: Combiné" "complexe 1" "(ls *.c > $TMPDIR/f) && (cat $TMPDIR/f | wc -l) && rm $TMPDIR/f"
    run_test "BONUS: Combiné" "complexe 2" "echo *.h && (false || echo backup) && echo *.c"
    run_test "BONUS: Combiné" "ultra complexe" "(echo *) && (ls *.c || echo none) && (true && echo final)"
}

# ================== SYNTHÈSE ==================
print_bar() {
    local ok=$1
    local ko=$2
    local total=$((ok+ko))
    local width=30
    local ok_len=$(( width * ok / total ))
    local ko_len=$(( width - ok_len ))
    local bar=""
    for ((i=0;i<ok_len;i++)); do bar+="\033[1;42m \033[0m"; done
    for ((i=0;i<ko_len;i++)); do bar+="\033[1;41m \033[0m"; done
    echo -e "$bar"
}

print_summary() {
    print_sep
    local percent=$(( 100 * OK_COUNT / TOTAL_COUNT ))
    local bonus_ok=0
    local bonus_ko=0
    local bonus_total=0
    local main_ok=0
    local main_ko=0
    local main_total=0
    # Catégories principales
    local main_cats=("COMMANDES SIMPLES" "VARIABLES D'ENVIRONNEMENT" "REDIRECTIONS" "PIPES" "BUILTINS" "QUOTES ET ÉCHAPPEMENT" "ERREURS" "TESTS SPÉCIAUX")
    # Catégories bonus
    local bonus_cats=("BONUS: Priorités" "BONUS: Wildcards" "BONUS: Combiné")
    # Stats principales
    for cat in "${main_cats[@]}"; do
        main_ok=$(( main_ok + ${OK_BY_CAT[$cat]:-0} ))
        main_ko=$(( main_ko + ${KO_BY_CAT[$cat]:-0} ))
    done
    main_total=$(( main_ok + main_ko ))
    # Stats bonus
    for cat in "${bonus_cats[@]}"; do
        bonus_ok=$(( bonus_ok + ${OK_BY_CAT[$cat]:-0} ))
        bonus_ko=$(( bonus_ko + ${KO_BY_CAT[$cat]:-0} ))
    done
    bonus_total=$(( bonus_ok + bonus_ko ))
    # Affichage général
    echo -e "${BOLD}${BLUE}========= SYNTHÈSE =========${RESET}"
    echo -e "\n========= SYNTHÈSE =========" >> "$TRACE"
    # Barre principale
    echo -e "\n${BOLD}Tests principaux :${RESET}"
    print_bar $main_ok $main_ko
    printf "${CYAN}Total${RESET} : ${GREEN}%3d${RESET} / ${YELLOW}%3d${RESET} OK (${GREEN}%3d%%${RESET})\n" "$main_ok" "$main_total" $((main_total==0?0:100*main_ok/main_total))
    printf "${CYAN}KO   ${RESET} : ${RED}%3d${RESET} / ${YELLOW}%3d${RESET} KO (${RED}%3d%%${RESET})\n" "$main_ko" "$main_total" $((main_total==0?0:100*main_ko/main_total))
    echo -e "\n${BOLD}Tableau par catégorie :${RESET}"
    printf "${BOLD}%-30s${RESET} | ${BOLD}OK${RESET} | ${BOLD}KO${RESET}\n" "Catégorie"
    for cat in "${main_cats[@]}"; do
        local ok=${OK_BY_CAT[$cat]:-0}
        local ko=${KO_BY_CAT[$cat]:-0}
        printf "%-30s | ${GREEN}%2d${RESET} | ${RED}%2d${RESET}\n" "$cat" "$ok" "$ko"
    done
    # BONUS séparé
    if [ $bonus_total -gt 0 ]; then
        echo -e "\n${BOLD}${MAGENTA}Tests BONUS :${RESET}"
        print_bar $bonus_ok $bonus_ko
        printf "${CYAN}Total BONUS${RESET} : ${GREEN}%3d${RESET} / ${YELLOW}%3d${RESET} OK (${GREEN}%3d%%${RESET})\n" "$bonus_ok" "$bonus_total" $((bonus_total==0?0:100*bonus_ok/bonus_total))
        printf "${CYAN}KO BONUS   ${RESET} : ${RED}%3d${RESET} / ${YELLOW}%3d${RESET} KO (${RED}%3d%%${RESET})\n" "$bonus_ko" "$bonus_total" $((bonus_total==0?0:100*bonus_ko/bonus_total))
        echo -e "\n${BOLD}Tableau BONUS :${RESET}"
        printf "${BOLD}%-30s${RESET} | ${BOLD}OK${RESET} | ${BOLD}KO${RESET}\n" "Catégorie BONUS"
        for cat in "${bonus_cats[@]}"; do
            local ok=${OK_BY_CAT[$cat]:-0}
            local ko=${KO_BY_CAT[$cat]:-0}
            printf "%-30s | ${GREEN}%2d${RESET} | ${RED}%2d${RESET}\n" "$cat" "$ok" "$ko"
        done
    fi
    if [ $KO_COUNT -ne 0 ]; then
        echo -e "\n${YELLOW}Des tests ont échoué. Consulte trace.txt pour les détails.${RESET}"
    else
        echo -e "\n${GREEN}Tous les tests sont passés avec succès !${RESET}"
    fi
}

# ================== MAIN ==================
run_all_tests
print_summary
